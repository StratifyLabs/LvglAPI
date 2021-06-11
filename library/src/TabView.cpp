#include "lvgl/TabView.hpp"

using namespace lv;

TabView::TabView(Object parent, const Create& options) {
  m_object = api()->tabview_create(
    parent.object(), static_cast<lv_dir_t>(options.direction()), options.size());
  set_name(options.name());
  auto tab_buttons = get_buttons();
  tab_buttons.set_name("TabViewButtons");
  auto content = get_content();
  content.set_name("TabViewContent");
}
