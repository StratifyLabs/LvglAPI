#include "lvgl/Arc.hpp"

using namespace lvgl;

Arc::Arc(Object parent, const Create & options): ObjectAccess(object_type()){
  m_object = api()->arc_create(parent.object());
  set_name(options.name());
}
