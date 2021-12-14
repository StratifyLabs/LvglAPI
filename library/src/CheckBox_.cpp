#include "lvgl/Checkbox.hpp"

using namespace lvgl;

Checkbox::Checkbox(const char * name){
  m_object = api()->checkbox_create(screen_object());
  set_user_data(m_object,name);
}
