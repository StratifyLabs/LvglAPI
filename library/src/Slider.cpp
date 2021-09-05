#include "lvgl/Slider.hpp"

using namespace lvgl;


Slider::Slider(Object parent, const Slider &){
  m_object = api()->slider_create(parent.object());
}
