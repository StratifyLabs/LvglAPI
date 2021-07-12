#include "lvgl/Calendar.hpp"
using namespace lvgl;

Calendar::Calendar(Object parent, const Create  & options): ObjectAccess(object_type()){
  m_object = api()->calendar_create(parent.object());
  set_name(options.name());
}
