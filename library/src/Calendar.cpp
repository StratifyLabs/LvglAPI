#include "lvgl/Calendar.hpp"
using namespace lvgl;

Calendar::Calendar(const char * name){
  m_object = api()->calendar_create(screen_object());
  set_user_data(m_object,name);
}

