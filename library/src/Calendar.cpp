#include "lvgl/Calendar.hpp"
using namespace lvgl;

Calendar::Calendar(Object parent, const Calendar &){
  m_object = api()->calendar_create(parent.object());
}

