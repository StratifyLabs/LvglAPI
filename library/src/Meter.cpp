#include "lvgl/Meter.hpp"

using namespace lvgl;

Meter::Meter(const char * name){
  m_object = api()->meter_create(screen_object());
  set_user_data(m_object,name);
}
