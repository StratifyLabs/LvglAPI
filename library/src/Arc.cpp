#include "lvgl/Arc.hpp"

using namespace lvgl;

Arc::Arc(Object parent, const Create & options){
  m_object = api()->arc_create(parent.object());
  set_name(options.name());
}


Arc::Arc(Object parent, const Arc & options): ObjectAccess(options.name()){
  m_object = api()->arc_create(parent.object());
}
