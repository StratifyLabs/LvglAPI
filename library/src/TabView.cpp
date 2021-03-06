#include "lvgl/TabView.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(TabView);

TabView::TabView(const Construct &options) {
  m_object = api()->tabview_create(
    screen_object(), static_cast<lv_dir_t>(options.direction), options.size);
  set_user_data(m_object, options.name);
}
