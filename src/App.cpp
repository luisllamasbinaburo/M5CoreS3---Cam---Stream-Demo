#include "PageManager.h"
#include "res/ResourcePool.h"
#include "pages/AppFactory.h"

void App_Init() {
    static AppFactory factory;
    static PageManager manager(&factory);

    /* Make sure the default group exists */
    if (!lv_group_get_default()) {
        lv_group_t* group = lv_group_create();
        lv_group_set_default(group);
    }

    /* Set screen style */
    lv_obj_t* scr = lv_scr_act();
    lv_obj_remove_style_all(scr);
    lv_obj_set_style_bg_opa(lv_scr_act(), LV_OPA_TRANSP, 0);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_disp_set_bg_color(lv_disp_get_default(), lv_color_white());

    /* Set root default style */
    static lv_style_t rootStyle;
    lv_style_init(&rootStyle);
    lv_style_set_width(&rootStyle, LV_HOR_RES);
    lv_style_set_height(&rootStyle, LV_VER_RES);
    lv_style_set_border_color(&rootStyle, lv_color_make(238, 238, 238));
    lv_style_set_border_width(&rootStyle, 0);
    lv_style_set_outline_width(&rootStyle, 0);
    lv_style_set_pad_all(&rootStyle, 0);
    manager.SetRootDefaultStyle(&rootStyle);

    /* Initialize resource pool */
    ResourcePool::Init();

    /* Initialize pages */
    manager.Install("AppCamera", "Pages/AppCamera");

    manager.SetGlobalLoadAnimType(PageManager::LOAD_ANIM_NONE);

    manager.Push("Pages/AppCamera");
}

void App_Uninit() {
}
