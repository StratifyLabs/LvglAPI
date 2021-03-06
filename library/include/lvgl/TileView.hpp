#ifndef LVGLAPI_LVGL_TILEVIEW_HPP
#define LVGLAPI_LVGL_TILEVIEW_HPP

#include "Generic.hpp"
#include "Object.hpp"

namespace lvgl {



class TileView : public ObjectAccess<TileView> {
public:
  explicit TileView(const char *name = "");
  explicit TileView(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t * get_class(){
    return api()->tileview_class;
  }

  class Location {
    API_AF(Location, uint8_t, row, 0);
    API_AF(Location, uint8_t, column, 0);
    API_AF(Location, Direction, direction, Direction::none);
    API_AF(Location, IsAnimate, is_animate, IsAnimate::yes);
  };

  TileView &add_tile(
    const char *name,
    const Location &location,
    void (*configure)(Generic) = nullptr);

  API_NO_DISCARD Object get_active_tile() const {
    return Object(api()->tileview_get_tile_act(m_object));
  }

  API_NO_DISCARD Object get_tile(const Location & location) const;

  API_NO_DISCARD Location get_active_tile_location() const {
    auto object = get_active_tile();
    return Location()
      .set_column(object.get_x() / get_content_width())
      .set_row(object.get_y() / get_content_height());
  }

  TileView &set_tile(const Location &location) {
    api()->obj_set_tile_id(
      object(), location.column(), location.row(),
      static_cast<lv_anim_enable_t>(location.is_animate()));
    return *this;
  }

  // must create the TileView with NavigationContext for these to work
  TileView &go_forward(const char * name, void (*configure)(Generic));
  TileView &go_forward(){
    return go_forward("", nullptr);
  }

  TileView &go_backward();

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_TILEVIEW_HPP
