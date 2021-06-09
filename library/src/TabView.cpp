#include "lvgl/TabView.hpp"

using namespace lv;

TabView::TabView(Object & parent, Direction direction, u32 size){
  m_is_created = true;

  printf("create tab %p\n", api()->tabview_create);

  m_object = api()->tabview_create(
      parent.object(),
      static_cast<lv_dir_t>(direction),
      size
      );
}
