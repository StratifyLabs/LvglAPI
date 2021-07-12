#include "lvgl/Roller.hpp"

using namespace lvgl;

Roller::Roller(Object parent, const Create& options): ObjectAccess(object_type()){
  m_object = api()->roller_create(parent.object());
  set_name(options.name());
}
