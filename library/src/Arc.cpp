
//Animation doesn't have a cpp file so this helps the parser
#include "lvgl/Animation.hpp"

#include "lvgl/Arc.hpp"

using namespace lvgl;

Arc::Arc(const char * name){
  m_object = api()->arc_create(screen_object());
  set_user_data(m_object,name);
}
