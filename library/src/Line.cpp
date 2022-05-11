#include "lvgl/Line.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(Line);

Line::Line(const char * name){
  construct_line(name);
}
