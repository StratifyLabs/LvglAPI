#include "lvgl/ColorWheel.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(ColorWheel);


ColorWheel::ColorWheel(const char * name, IsKnobRecolor is_knob_recolor){
  m_object = api()->colorwheel_create(screen_object(), bool(is_knob_recolor));
  set_user_data(m_object,name);
}
