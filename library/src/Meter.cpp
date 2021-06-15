#include "lvgl/Meter.hpp"

using namespace lv;

Meter::Meter(Object parent, const Create & options){
  m_object = api()->meter_create(parent.object());
  set_name(options.name());
}
