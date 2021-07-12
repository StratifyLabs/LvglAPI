#include "lvgl/Checkbox.hpp"

using namespace lvgl;

Checkbox::Checkbox(Object parent, const Create& options): ObjectAccess(object_type()){
  m_object = api()->checkbox_create(parent.object());
  set_name(options.name());
}
