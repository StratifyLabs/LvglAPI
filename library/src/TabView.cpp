#include "lvgl/TabView.hpp"

using namespace lv;

TabView::TabView(const char* name, Direction direction, u32 size){
  m_object = api()->tabview_create(
      lv_scr_act(),
      static_cast<lv_dir_t>(direction),
      size
      );
  set_name(name);
}
