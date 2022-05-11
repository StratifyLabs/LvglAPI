#include "lvgl/Chart.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(Chart);


Chart::Chart(const char * name){
  m_object = api()->chart_create(screen_object());
  set_user_data(m_object,name);
}
