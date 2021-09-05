#include "lvgl/Line.hpp"

using namespace lvgl;

Line::Line(Object parent, const Create& options){
  m_object = api()->line_create(parent.object());
  set_name(options.name());
}


Line::Line(Object parent, const Line&){
  m_object = api()->line_create(parent.object());
}
