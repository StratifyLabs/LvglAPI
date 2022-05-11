#include "lvgl/Meter.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(Meter);

Meter::Meter(const char * name){
  m_object = api()->meter_create(screen_object());
  set_user_data(m_object,name);
}
