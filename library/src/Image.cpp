#include "lvgl/Image.hpp"

using namespace lvgl;


Image::Image(const char * name){
  m_object = api()->img_create(screen_object());
  set_user_data(m_object,name);
}
