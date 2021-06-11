#include "lvgl/Bar.hpp"

using namespace lv;

Bar::Bar(Object parent, const Create& options){
  m_object = api()->bar_create(parent.object());
  set_name(options.name());
}
