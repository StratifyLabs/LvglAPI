#include "lvgl/Roller.hpp"

using namespace lvgl;

Roller::Roller(Object parent, const Create& options){
  m_object = api()->roller_create(parent.object());
  set_name(options.name());
}


Roller::Roller(Object parent, const Roller&){
  m_object = api()->roller_create(parent.object());
}
