#include "lvgl/TabView.hpp"

using namespace lv;

TabView::TabView(Direction direction, u32 size, Object parent){
  m_object = api()->tabview_create(
      lv_scr_act(),
      static_cast<lv_dir_t>(direction),
      size
      );
}
