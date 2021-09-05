#include "lvgl/Slider.hpp"

using namespace lvgl;


Slider::Slider(Object parent, const Slider &){
  m_object = api()->slider_create(parent.object());
}

Slider::Slider(Object parent, const Create & options){
  m_object = api()->slider_create(parent.object());
  set_name(options.name());
}
