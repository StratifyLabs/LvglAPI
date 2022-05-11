#include "lvgl/CheckBox.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(CheckBox);


CheckBox::CheckBox(const char * name){
  m_object = api()->checkbox_create(screen_object());
  set_user_data(m_object,name);
}
