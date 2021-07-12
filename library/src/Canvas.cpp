#include "lvgl/Canvas.hpp"

using namespace lvgl;


Canvas::Canvas(Object parent, const Create & options) : ObjectAccess(object_type()){
  m_object =
    lv_canvas_create(parent.object());
  set_name(options.name());
}
