#include "lvgl/ImageButton.hpp"

using namespace lvgl;

ImageButton::ImageButton(const char * name) {
  set_user_data(m_object,name);

}
