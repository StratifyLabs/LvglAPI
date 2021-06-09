#ifndef LVGLAPI_LVGL_BUTTON_HPP
#define LVGLAPI_LVGL_BUTTON_HPP

#include "Object.hpp"

namespace lv {

class Button : public ObjectAccess<Button> {
public:
  Button(Object & parent){
    m_object = lv_btn_create(parent.object());
    m_is_created = true;
  }

};

} // namespace lv

#endif // LVGLAPI_LVGL_BUTTON_HPP
