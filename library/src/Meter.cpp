#include "lvgl/Meter.hpp"

using namespace lvgl;

Meter::Meter(Object parent, const Create & options){
  m_object = api()->meter_create(parent.object());
  set_name(options.name());
}

Meter::Meter(Object parent, const Meter &){
  m_object = api()->meter_create(parent.object());
}
