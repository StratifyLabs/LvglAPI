#ifndef LVGLAPI_LVGL_KEYBOARD_HPP
#define LVGLAPI_LVGL_KEYBOARD_HPP

#include "ObjectAccess.hpp"
#include "TextArea.hpp"
#include "ButtonMatrix.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

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

  explicit Keyboard(const char * name) : ObjectAccess(name){}

  Keyboard & set_text_area(TextArea text_area){
    api()->keyboard_set_textarea(object(), text_area.object());
    return *this;
  }

  Keyboard & set_mode(Mode value){
    api()->keyboard_set_mode(object(), static_cast<lv_keyboard_mode_t>(value));
    return *this;
  }

  TextArea get_text_area() const {
    return TextArea(api()->keyboard_get_textarea(object()));
  }

  Mode get_mode() const {
    return Mode(api()->keyboard_get_mode(object()));
  }

  const char ** get_map_array() const {
    return api()->btnmatrix_get_map(object());
  }

  ButtonMatrix get_button_matrix() const {
    return ButtonMatrix(&(reinterpret_cast<lv_keyboard_t*>(m_object)->btnm));
  }

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Keyboard(lv_obj_t * object){ m_object = object; }
  Keyboard(Object parent, const Keyboard &);

};

}

#endif // LVGLAPI_LVGL_KEYBOARD_HPP
