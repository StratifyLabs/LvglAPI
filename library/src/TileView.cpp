#include "lvgl/TileView.hpp"

using namespace lvgl;

TileView::TileView(Object parent, const TileView &){
  m_object = api()->tileview_create(parent.object());
}
