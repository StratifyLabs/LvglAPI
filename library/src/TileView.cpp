#include "lvgl/TileView.hpp"

using namespace lv;

TileView::TileView(Object parent, const Create& options){
  m_object = api()->tileview_create(parent.object());
  set_name(options.name());
}
