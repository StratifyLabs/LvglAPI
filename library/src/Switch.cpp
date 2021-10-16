#include "lvgl/Switch.hpp"

using namespace lvgl;

Switch::Switch(const char * name){
  m_object = api()->switch_create(screen_object());
  set_user_data(m_object,name);
}
