#include "lvgl/TileView.hpp"

using namespace lvgl;

TileView::TileView(Object parent, const Create& options): ObjectAccess(object_type()){
  m_object = api()->tileview_create(parent.object());
  set_name(options.name());
}
