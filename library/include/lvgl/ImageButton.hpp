#ifndef LVGLAPI_LVGL_IMAGEBUTTON_HPP
#define LVGLAPI_LVGL_IMAGEBUTTON_HPP

#include "ObjectAccess.hpp"

namespace lvgl {


class ImageButton : public ObjectAccess<ImageButton>
{
public:
  explicit ImageButton(const char * name = "");
  explicit ImageButton(lv_obj_t * object){ m_object = object; }


  static const lv_obj_class_t * get_class(){
    return api()->image_button_class;
  }

};

}

#endif // LVGLAPI_LVGL_IMAGEBUTTON_HPP
