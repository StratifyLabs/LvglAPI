#include "lvgl/Switch.hpp"

using namespace lv;

Switch::Switch(Object parent, const Create& options)
{
  m_object = api()->switch_create(parent.object());
  set_name(options.name());
}
