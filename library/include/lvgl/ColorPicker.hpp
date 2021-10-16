#ifndef LVGLAPI_LVGL_COLORPICKER_HPP
#define LVGLAPI_LVGL_COLORPICKER_HPP

#include "ObjectAccess.hpp"

namespace lvgl {


class ColorPicker : public ObjectAccess<ColorPicker>
{
public:
  explicit ColorPicker(const char * name);
  explicit ColorPicker(lv_obj_t * object){ m_object = object; }

  static const lv_obj_class_t * get_class(){
    return api()->colorwheel_class;
  }

};

}

#endif // LVGLAPI_LVGL_COLORPICKER_HPP
