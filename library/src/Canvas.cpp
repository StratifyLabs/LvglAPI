#include "lvgl/Canvas.hpp"

using namespace lvgl;

Canvas::Canvas(Object parent, const Canvas &){
  m_object =
    lv_canvas_create(parent.object());
}
