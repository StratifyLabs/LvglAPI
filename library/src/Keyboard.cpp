#include "lvgl/Keyboard.hpp"

using namespace lvgl;

Keyboard::Keyboard(Object parent, const Create& options){
  m_object = api()->keyboard_create(parent.object());
  set_name(options.name());
}

Keyboard::Keyboard(Object parent, const Keyboard&){
  m_object = api()->keyboard_create(parent.object());
}
