#include "lvgl/Checkbox.hpp"

using namespace lvgl;

Checkbox::Checkbox(Object parent, const Create& options){
  m_object = api()->checkbox_create(parent.object());
  set_name(options.name());
}

Checkbox::Checkbox(Object parent, const Checkbox&){
  m_object = api()->checkbox_create(parent.object());
}
