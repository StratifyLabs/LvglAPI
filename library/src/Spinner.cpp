#include "lvgl/Spinner.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(Spinner);


Spinner::Spinner(const Construct &options) {
  m_object = api()->spinner_create(screen_object(), options.time, options.arc_length);
  set_user_data(m_object, options.name);
}

Spinner::Spinner(const char *name) {
  m_object = api()->spinner_create(screen_object(), 1000, 60);
  set_user_data(m_object, name);
}
