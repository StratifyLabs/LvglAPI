#include <fs/ViewFile.hpp>

#include "lvgl/Bar.hpp"
#include "lvgl/Event.hpp"
#include "lvgl/TextArea.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(TextArea);

TextArea::TextArea(const char *name) {
  m_object = api()->textarea_create(screen_object());
  set_user_data(m_object, name);
}


