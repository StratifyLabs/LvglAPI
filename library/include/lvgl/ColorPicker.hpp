#ifndef LVGLAPI_LVGL_COLORPICKER_HPP
#define LVGLAPI_LVGL_COLORPICKER_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class ColorPicker : public ObjectAccess<ColorPicker>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  explicit ColorPicker(const char * name) : ObjectAccess(name){}

private:
  OBJECT_ACCESS_FRIENDS();
  explicit ColorPicker(lv_obj_t * object){ m_object = object; }
  ColorPicker(Object parent, const ColorPicker &);
  ColorPicker(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_COLORPICKER_HPP
