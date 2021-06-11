#include "lvgl/Line.hpp"

using namespace lv;

Line::Line(Object parent, const Create& options){
  m_object = api()->line_create(parent.object());
  set_name(options.name());
}
