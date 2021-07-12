#include "lvgl/Keyboard.hpp"

using namespace lvgl;

Keyboard::Keyboard(Object parent, const Create& options): ObjectAccess(object_type()){
  m_object = api()->keyboard_create(parent.object());
  set_name(options.name());
}
