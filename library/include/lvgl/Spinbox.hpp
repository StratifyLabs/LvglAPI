#ifndef LVGLAPI_LVGL_SPINBOX_HPP
#define LVGLAPI_LVGL_SPINBOX_HPP

#include "Object.hpp"

namespace lv {

class SpinBox : public ObjectAccess<SpinBox>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  SpinBox(Object parent, const Create & options);
};

}
#endif // LVGLAPI_LVGL_SPINBOX_HPP
