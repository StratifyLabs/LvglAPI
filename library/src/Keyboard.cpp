#include "lvgl/Keyboard.hpp"

using namespace lvgl;

Keyboard::Keyboard(const char * name){
  m_object = api()->keyboard_create(screen_object());
  set_user_data(m_object,name);
}
