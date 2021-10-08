#ifndef LVGLAPI_LVGL_COLORPICKER_HPP
#define LVGLAPI_LVGL_COLORPICKER_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class ColorPicker : public ObjectAccess<ColorPicker>
{
public:
  explicit ColorPicker(const char * name) : ObjectAccess(name){}
  explicit ColorPicker(const Context & context) : ObjectAccess(context.cast_as_name()){}

  static const lv_obj_class_t * get_class(){
    return api()->colorwheel_class;
  }
private:
  OBJECT_ACCESS_FRIENDS();
  explicit ColorPicker(lv_obj_t * object){ m_object = object; }
  ColorPicker(Object parent, const ColorPicker &);
};

}

#endif // LVGLAPI_LVGL_COLORPICKER_HPP
