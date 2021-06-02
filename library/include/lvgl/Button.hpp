#ifndef LVGLAPI_LVGL_BUTTON_HPP
#define LVGLAPI_LVGL_BUTTON_HPP

#include "Object.hpp"

namespace lv {

class Button : public ContainerAccess<Button> {
public:
  Button(Object & parent, const Button * copy = nullptr){
    m_object = lv_btn_create(parent.object(), copy ? copy->object() : nullptr);
  }

  enum class State {
    released = LV_BTN_STATE_RELEASED,
    pressed = LV_BTN_STATE_PRESSED,
    disabled = LV_BTN_STATE_DISABLED,
    checked_released = LV_BTN_STATE_CHECKED_RELEASED,
    checked_pressed = LV_BTN_STATE_CHECKED_PRESSED,
    checked_disabled = LV_BTN_STATE_CHECKED_DISABLED
  };

  enum class Part {
    main = LV_BTN_PART_MAIN
  };


  State get_button_state() const {
    return State(lv_btn_get_state(object()));
  }

  bool is_checkable() const {
    return lv_btn_get_checkable(object());
  }

  Layout get_layout() const {
    return Layout(lv_btn_get_layout(object()));
  }

  Button & set_checkable(bool value = true ){
    lv_btn_set_checkable(object(), value);
    return *this;
  }

  Button & set_button_state(State value){
    lv_btn_set_state(m_object, static_cast<lv_btn_state_t>(value));
    return *this;
  }

  Button & toggle(){
    lv_btn_toggle(m_object);
    return *this;
  }


};

} // namespace lv

#endif // LVGLAPI_LVGL_BUTTON_HPP
