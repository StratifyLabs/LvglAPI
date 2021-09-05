#include "lvgl/Canvas.hpp"

using namespace lvgl;


Canvas::Canvas(Object parent, const Create & options){
  m_object =
    lv_canvas_create(parent.object());
  set_name(options.name());
}

Canvas::Canvas(Object parent, const Canvas &){
  m_object =
    lv_canvas_create(parent.object());
}
