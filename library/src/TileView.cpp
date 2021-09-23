#include "lvgl/TileView.hpp"
#include "lvgl/Event.hpp"

using namespace lvgl;

TileView::TileView(Object parent, const TileView &) {
  m_object = api()->tileview_create(parent.object());
}

Object TileView::get_tile(const Location &location) const {
  // search the children for a tile at the location
  const lv_coord_t x = location.column() * get_content_width();
  const lv_coord_t y = location.row() * get_content_height();
  for (size_t i = 0; i < get_child_count(); i++) {
    auto object = get_child(i);
    if (object.is_valid()) {
      if (object.get_x() == x && object.get_y() == y) {
        return object;
      }
    }
  }
  return Object();
}

TileView &TileView::go_forward(const char *name, void (*configure)(Container &)) {
  auto active_location = get_active_tile_location();
  auto next_location = Location(active_location).set_column(active_location.column() + 1);

  // check for a tile in the next location -- remove it if needed
  if (configure) {
    auto tile_to_remove = get_tile(next_location);
    if (tile_to_remove.is_valid()) {
      tile_to_remove.remove();
    }

    add_tile(
      name, Location(active_location).set_column(active_location.column() + 1),
      configure);
  }

  set_tile(next_location).update_layout();
  Event::send(get_active_tile(), EventCode::focused);
  return *this;
}

TileView &TileView::go_backward() {
  auto active_location = get_active_tile_location();
  if (active_location.column() == 0) {
    return *this;
  }

  auto next_location = Location(active_location).set_column(active_location.column() - 1);

  set_tile(next_location).update_layout();
  Event::send(get_active_tile(), EventCode::focused);
  return *this;
}
