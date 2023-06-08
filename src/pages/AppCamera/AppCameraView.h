#ifndef __APPCAMERA_VIEW_H
#define __APPCAMERA_VIEW_H

#include "../Page.h"

namespace Page {

class AppCameraView {
   public:
    void Create(lv_obj_t* root);
    void Delete();

   public:
    struct {
    } ui;

   private:
};

}  // namespace Page

#endif  // !__VIEW_H
