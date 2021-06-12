#include "lvgl/Roller.hpp"

using namespace lv;

Roller::Roller(Object parent, const Create& options)
{
  m_object = api()->roller_create(parent.object());
  set_name(options.name());
}
