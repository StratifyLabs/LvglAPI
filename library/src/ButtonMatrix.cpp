#include "lvgl/ButtonMatrix.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(ButtonMatrix);

ButtonMatrix::ButtonMatrix(const char * name){
  m_object = api()->btnmatrix_create(screen_object());
  set_user_data(m_object,name);
}
