#include "lvgl/Calendar.hpp"
using namespace lv;

Calendar::Calendar(Object parent, const Create  & options){
  m_object = api()->calendar_create(parent.object());
  set_name(options.name());
}
