#include "lvgl/TileView.hpp"

using namespace lvgl;

TileView::TileView(Object parent, const Create& options){
  m_object = api()->tileview_create(parent.object());
  set_name(options.name());
}

TileView::TileView(Object parent, const TileView &){
  m_object = api()->tileview_create(parent.object());
}
