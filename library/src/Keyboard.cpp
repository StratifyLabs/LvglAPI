#include "lvgl/Keyboard.hpp"

using namespace lvgl;

Keyboard::Keyboard(Object parent, const Keyboard&){
  m_object = api()->keyboard_create(parent.object());
}
