#include "lvgl/Arc.hpp"

using namespace lv;

Arc::Arc(Object parent, const Create & options){
  m_object = api()->arc_create(parent.object());
  set_name(options.name());
}
