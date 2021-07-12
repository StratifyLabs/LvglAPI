#include "lvgl/Meter.hpp"

using namespace lvgl;

Meter::Meter(Object parent, const Create & options): ObjectAccess(object_type()){
  m_object = api()->meter_create(parent.object());
  set_name(options.name());
}
