#include "lvgl/Roller.hpp"

using namespace lvgl;

Roller::Roller(const char * name){
  m_object = api()->roller_create(screen_object());
  set_user_data(m_object,name);
}
