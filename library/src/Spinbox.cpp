#include "lvgl/Spinbox.hpp"

using namespace lvgl;

Spinbox::Spinbox(const char * name){
  //m_object = api()->spinbox_create(screen_object());
  set_user_data(m_object,name);
}
