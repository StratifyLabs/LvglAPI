#include "lvgl/Bar.hpp"

using namespace lvgl;

Bar::Bar(Object parent, const Create& options): BarAccess(object_type()){
  m_object = api()->bar_create(parent.object());
  set_name(options.name());
}
