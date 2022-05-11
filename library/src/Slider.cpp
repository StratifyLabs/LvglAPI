#include "lvgl/Slider.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(Slider);


Slider::Slider(const char * name){
  m_object = api()->slider_create(screen_object());
  set_user_data(m_object,name);
}
