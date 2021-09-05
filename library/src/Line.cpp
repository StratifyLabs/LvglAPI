#include "lvgl/Line.hpp"

using namespace lvgl;

Line::Line(Object parent, const Line&){
  m_object = api()->line_create(parent.object());
}
