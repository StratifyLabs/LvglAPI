#include "lvgl/Checkbox.hpp"

using namespace lv;

Checkbox::Checkbox(Object parent, const Create& options){
  m_object = api()->checkbox_create(parent.object());
  set_name(options.name());
}
