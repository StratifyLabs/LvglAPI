#include "lvgl/Roller.hpp"

using namespace lvgl;

Roller::Roller(Object parent, const Roller&){
  m_object = api()->roller_create(parent.object());
}
