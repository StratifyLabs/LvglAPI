#include "lvgl/Line.hpp"

using namespace lvgl;

Line::Line(const char * name){
  m_object = api()->line_create(screen_object());
  set_user_data(m_object,name);
}
