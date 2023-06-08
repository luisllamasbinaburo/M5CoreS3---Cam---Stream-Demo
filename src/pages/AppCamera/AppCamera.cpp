#include "AppCamera.h"

void startCameraServer();

using namespace Page;

AppCamera::AppCamera() : timer(nullptr) {
}

AppCamera::~AppCamera() {
}

void AppCamera::onCustomAttrConfig() {
    LV_LOG_USER(__func__);
}

void AppCamera::onViewLoad() {
    LV_LOG_USER(__func__);
    View.Create(_root);

    Model.LTR553Init();
    Model.CameraInit();
  
    startCameraServer();

    AttachEvent(_root);
}

void AppCamera::onViewDidLoad() {
    LV_LOG_USER(__func__);
}

void AppCamera::onViewWillAppear() {
    LV_LOG_USER(__func__);

    timer = lv_timer_create(onTimerUpdate, 30, this);
}

void AppCamera::onViewDidAppear() {
    LV_LOG_USER(__func__);
}

void AppCamera::onViewWillDisappear() {
    LV_LOG_USER(__func__);
}

void AppCamera::onViewDidDisappear() {
    LV_LOG_USER(__func__);
    lv_timer_del(timer);
}

void AppCamera::onViewUnload() {
    LV_LOG_USER(__func__);

    View.Delete();
    Model.ReleaseFramebuffer();
    Model.CameraDeinit();
}

void AppCamera::onViewDidUnload() {
    LV_LOG_USER(__func__);
}

void AppCamera::AttachEvent(lv_obj_t* obj, lv_event_code_t code) {
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, code, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void AppCamera::Update() {
    if (M5.Display.getBrightness() < 100) {
        M5.Display.setBrightness(M5.Display.getBrightness() + 5);
    }

    if (Model.GetFramebuffer()) {
        M5.Display.startWrite();
        M5.Display.setAddrWindow(0, 0, 320, 240);
        M5.Display.writePixels((uint16_t*)Model.fb->buf,
                               int(Model.fb->len / 2));
        M5.Display.endWrite();
    }
    Model.ReleaseFramebuffer();
}

void AppCamera::onTimerUpdate(lv_timer_t* timer) {
    AppCamera* instance = (AppCamera*)timer->user_data;

    instance->Update();
}

void AppCamera::onEvent(lv_event_t* event) {
    AppCamera* instance = (AppCamera*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj        = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);
}
