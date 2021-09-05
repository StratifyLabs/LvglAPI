#include "lvgl/Switch.hpp"

using namespace lvgl;

Switch::Switch(Object parent, const Switch&){
  m_object = api()->switch_create(parent.object());
}
