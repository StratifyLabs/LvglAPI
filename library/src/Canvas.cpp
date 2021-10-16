#include "lvgl/Canvas.hpp"

using namespace lvgl;

Canvas::Canvas(const char * name){
  m_object =
    lv_canvas_create(screen_object());
  set_user_data(m_object,name);
}
