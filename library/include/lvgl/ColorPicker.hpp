#ifndef LVGLAPI_LVGL_COLORPICKER_HPP
#define LVGLAPI_LVGL_COLORPICKER_HPP

#include "ObjectAccess.hpp"

namespace lvgl {

class ColorPicker : public ObjectAccess<ColorPicker>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  ColorPicker(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_COLORPICKER_HPP
