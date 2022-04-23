#ifndef LVGLAPI_LVGL_KEYBOARD_HPP
#define LVGLAPI_LVGL_KEYBOARD_HPP

#include "ObjectAccess.hpp"
#include "TextArea.hpp"
#include "ButtonMatrix.hpp"

namespace lvgl {


class Keyboard : public ObjectAccess<Keyboard> {
public:

  static constexpr auto newline = LV_SYMBOL_NEW_LINE;

  enum class Mode {
    text_lower = LV_KEYBOARD_MODE_TEXT_LOWER,
    text_upper = LV_KEYBOARD_MODE_TEXT_UPPER,
    special = LV_KEYBOARD_MODE_SPECIAL,
    number = LV_KEYBOARD_MODE_NUMBER,
    user1 = LV_KEYBOARD_MODE_USER_1,
    user2 = LV_KEYBOARD_MODE_USER_2,
    user3 = LV_KEYBOARD_MODE_USER_3,
    hex = LV_KEYBOARD_MODE_USER_4,
  };

  static const char * to_cstring(Mode value);
  static Mode get_mode(var::StringView value);

  LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Keyboard);

  static const lv_obj_class_t * get_class(){
    return api()->keyboard_class;
  }

  Keyboard & set_text_area(TextArea text_area);
  Keyboard & set_mode(Mode value);
  Keyboard & set_map(
    Mode mode,
    const char ** map, const lv_btnmatrix_ctrl_t * control_map);

  API_NO_DISCARD TextArea get_text_area() const;
  API_NO_DISCARD Mode get_mode() const;
  API_NO_DISCARD const char ** get_map_array() const;
  API_NO_DISCARD ButtonMatrix get_button_matrix() const;
};

}

#endif // LVGLAPI_LVGL_KEYBOARD_HPP
