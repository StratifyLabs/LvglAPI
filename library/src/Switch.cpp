#include "lvgl/Switch.hpp"

using namespace lvgl;


Switch::Switch(Object parent, const Create& options){
  m_object = api()->switch_create(parent.object());
  set_name(options.name());
}

Switch::Switch(Object parent, const Switch&){
  m_object = api()->switch_create(parent.object());
}
