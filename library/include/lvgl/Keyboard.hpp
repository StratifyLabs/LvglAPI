#ifndef LVGLAPI_LVGL_KEYBOARD_HPP
#define LVGLAPI_LVGL_KEYBOARD_HPP

#include "ObjectAccess.hpp"
#include "TextArea.hpp"
#include "ButtonMatrix.hpp"

namespace lvgl {


class Keyboard : public ObjectAccess<Keyboard>
{
public:

  static constexpr auto newline = LV_SYMBOL_NEW_LINE;

  enum class Mode {
    text_lower = LV_KEYBOARD_MODE_TEXT_LOWER,
    text_upper = LV_KEYBOARD_MODE_TEXT_UPPER,
    special = LV_KEYBOARD_MODE_SPECIAL,
    number = LV_KEYBOARD_MODE_NUMBER
  };

  LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Keyboard);

  static const lv_obj_class_t * get_class(){
    return api()->keyboard_class;
  }

  Keyboard & set_text_area(TextArea text_area){
    api()->keyboard_set_textarea(object(), text_area.object());
    return *this;
  }

  Keyboard & set_mode(Mode value){
    api()->keyboard_set_mode(object(), static_cast<lv_keyboard_mode_t>(value));
    return *this;
  }

  Keyboard & set_map(
    Mode mode,
    const char ** map, const lv_btnmatrix_ctrl_t * control_map){
    api()->keyboard_set_map(object(), lv_keyboard_mode_t(mode), map, control_map);
    return *this;
  }

  API_NO_DISCARD TextArea get_text_area() const {
    return TextArea(api()->keyboard_get_textarea(object()));
  }

  API_NO_DISCARD Mode get_mode() const {
    return Mode(api()->keyboard_get_mode(object()));
  }

  API_NO_DISCARD const char ** get_map_array() const {
    return api()->btnmatrix_get_map(object());
  }

  API_NO_DISCARD ButtonMatrix get_button_matrix() const {
    return ButtonMatrix(&(reinterpret_cast<lv_keyboard_t*>(m_object)->btnm));
  }

};

}

#endif // LVGLAPI_LVGL_KEYBOARD_HPP
