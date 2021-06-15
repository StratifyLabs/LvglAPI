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

  Checkbox & set_text(const char * text){
    api()->checkbox_set_text(object(), text);
    return *this;
  }

  Checkbox & set_static_text(const char * text){
    api()->checkbox_set_text_static(object(), text);
    return *this;
  }

  const char * get_text() const {
    return api()->checkbox_get_text(object());
  }
};

}

#endif // LVGLAPI_LVGL_CHECKBOX_HPP
