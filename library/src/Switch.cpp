#include "lvgl/Switch.hpp"

using namespace lvgl;

Switch::Switch(Object parent, const Create& options): ObjectAccess(object_type()){
  m_object = api()->switch_create(parent.object());
  set_name(options.name());
}
