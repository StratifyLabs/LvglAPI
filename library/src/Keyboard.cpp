#include "lvgl/Keyboard.hpp"

using namespace lv;

Keyboard::Keyboard(Object parent, const Create& options)
{
  m_object = api()->keyboard_create(parent.object());
  set_name(options.name());
}
