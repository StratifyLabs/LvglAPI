#include "lvgl/SpinBox.hpp"

using namespace lvgl;

SpinBox::SpinBox(const char * name){
  m_object = api()->spinbox_create(screen_object());
  set_user_data(m_object,name);
}
