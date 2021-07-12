#include "lvgl/Line.hpp"

using namespace lvgl;

Line::Line(Object parent, const Create& options): ObjectAccess(object_type()){
  m_object = api()->line_create(parent.object());
  set_name(options.name());
}
