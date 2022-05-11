#include "lvgl/ImageButton.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(ImageButton);


ImageButton::ImageButton(const char * name) {
  m_object = api()->imgbtn_create(screen_object());
  set_user_data(m_object,name);
}
