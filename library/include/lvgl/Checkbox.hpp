#ifndef LVGLAPI_LVGL_CHECKBOX_HPP
#define LVGLAPI_LVGL_CHECKBOX_HPP

#include "Object.hpp"

namespace lv {

class Checkbox : public ObjectAccess<Checkbox>{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  Checkbox(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_CHECKBOX_HPP
