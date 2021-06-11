#ifndef LVGLAPI_LVGL_BUTTON_HPP
#define LVGLAPI_LVGL_BUTTON_HPP

#include "Object.hpp"

namespace lv {

class Button : public ObjectAccess<Button> {
public:

  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };

  Button(Object parent, const Create & options){
    m_object = api()->btn_create(parent.object());
    set_name(options.name());
  }

};

} // namespace lv

#endif // LVGLAPI_LVGL_BUTTON_HPP
