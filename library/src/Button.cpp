#include "lvgl/Button.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(Button);

Button::Button(const char * name){
  m_object = api()->btn_create(screen_object());
  set_user_data(m_object, name);
}
