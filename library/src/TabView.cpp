#include "lvgl/TabView.hpp"

using namespace lvgl;

TabView::TabView(Object parent, const TabView& options){
  m_object = api()->tabview_create(
    parent.object(), static_cast<lv_dir_t>(options.m_construct->direction()), options.m_construct->size());


  auto tab_buttons = get_buttons();
  tab_buttons.set_name("TabViewButtons");
  auto content = get_content();
  content.set_name("TabViewContent");
}

