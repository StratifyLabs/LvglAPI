#include "lvgl/Keyboard.hpp"

using namespace lvgl;

Keyboard::Keyboard(const char * name){
  m_object = api()->keyboard_create(screen_object());
  set_user_data(m_object,name);
}


const char * Keyboard::to_cstring(Mode value){
  switch (value) {
    LVGL_PROPERTY_CASE(Mode, text_lower);
    LVGL_PROPERTY_CASE(Mode, text_upper);
    LVGL_PROPERTY_CASE(Mode, special);
    LVGL_PROPERTY_CASE(Mode, number);
    LVGL_PROPERTY_CASE(Mode, user1);
    LVGL_PROPERTY_CASE(Mode, user2);
    LVGL_PROPERTY_CASE(Mode, user3);
    LVGL_PROPERTY_CASE(Mode, hex);
  }
  return "unknown";
}

Keyboard::Mode Keyboard::get_mode(var::StringView value){
  LVGL_PROPERTY_STRING_CASE(Mode, text_upper);
  LVGL_PROPERTY_STRING_CASE(Mode, special);
  LVGL_PROPERTY_STRING_CASE(Mode, number);
  LVGL_PROPERTY_STRING_CASE(Mode, user1);
  LVGL_PROPERTY_STRING_CASE(Mode, user2);
  LVGL_PROPERTY_STRING_CASE(Mode, user3);
  LVGL_PROPERTY_STRING_CASE(Mode, hex);
  return Mode::text_lower;
}


Keyboard &Keyboard::set_mode(Keyboard::Mode value) {
  if( value == Mode::hex ){
    static constexpr char * hex_keyboard_map[]
      = {"1",  "2", "3",  LV_SYMBOL_KEYBOARD,  "\n",
         "4",  "5", "6",  LV_SYMBOL_OK,        "\n",
         "7",  "8", "9",  LV_SYMBOL_BACKSPACE, "\n",
         "0x", "0", "00", LV_SYMBOL_LEFT,      LV_SYMBOL_RIGHT,
         ""};

    static constexpr lv_btnmatrix_ctrl_t hex_keyboard_control_map[] = {
      1,
      1,
      1,
      LV_KEYBOARD_CTRL_BTN_FLAGS | 2,
      1,
      1,
      1,
      LV_KEYBOARD_CTRL_BTN_FLAGS | 2,
      1,
      1,
      1,
      2,
      1,
      1,
      1,
      1,
      1};

    set_map(
      Keyboard::Mode::number,
      (const char **)hex_keyboard_map,
      hex_keyboard_control_map);

    api()->keyboard_set_mode(object(), static_cast<lv_keyboard_mode_t>(Keyboard::Mode::number));

  } else {
    api()->keyboard_set_mode(object(), static_cast<lv_keyboard_mode_t>(value));
  }
  return *this;
}

Keyboard &Keyboard::set_map(
  Keyboard::Mode mode,
  const char **map,
  const lv_btnmatrix_ctrl_t *control_map) {
  api()->keyboard_set_map(object(), lv_keyboard_mode_t(mode), map, control_map);
  return *this;
}

TextArea Keyboard::get_text_area() const {
  return TextArea(api()->keyboard_get_textarea(object()));
}

Keyboard::Mode Keyboard::get_mode() const {
  return Mode(api()->keyboard_get_mode(object()));
}

const char **Keyboard::get_map_array() const {
  return api()->btnmatrix_get_map(object());
}

ButtonMatrix Keyboard::get_button_matrix() const {
  return ButtonMatrix(&(reinterpret_cast<lv_keyboard_t*>(m_object)->btnm));
}

Keyboard &Keyboard::set_text_area(TextArea text_area) {
  api()->keyboard_set_textarea(object(), text_area.object());
  return *this;
}
