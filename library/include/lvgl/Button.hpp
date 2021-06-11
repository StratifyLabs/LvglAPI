#ifndef LVGLAPI_LVGL_BUTTON_HPP
#define LVGLAPI_LVGL_BUTTON_HPP

#include "Object.hpp"

namespace lv {

class Button : public ObjectAccess<Button> {
public:
  Button(const char * name){
    m_object = lv_btn_create(Container::active_screen().object());
    set_name(name);
  }

};

} // namespace lv

#endif // LVGLAPI_LVGL_BUTTON_HPP
