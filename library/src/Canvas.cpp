#include "lvgl/Canvas.hpp"

using namespace lv;


Canvas::Canvas(Object parent, const Create & options) {
  m_object =
    lv_canvas_create(parent.object());
  set_name(options.name());
}
