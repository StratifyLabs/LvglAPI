#ifndef LVGLAPI_LVGL_TILEVIEW_HPP
#define LVGLAPI_LVGL_TILEVIEW_HPP

#include "Container.hpp"

namespace lvgl {

class TileView : public ObjectAccess<TileView> {
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char *name) : CreateAccess(name) {}
  };
  TileView(Object parent, const Create &options);

  class Location {
    API_AF(Location, uint8_t, row, 0);
    API_AF(Location, uint8_t, column, 0);
    API_AF(Location, Direction, direction, Direction::none);
    API_AF(Location, IsAnimate, is_animate, IsAnimate::yes);
  };

  TileView &add_tile(
    const char * name,
    const Location &location,
    void (*add)(Container &container) = nullptr) {
    Container obj(api()->tileview_add_tile(
      m_object, location.column(), location.row(),
      static_cast<lv_dir_t>(location.direction())));
    obj.set_name(name);
    //obj.m_object->user_data = (void*)name;
    if (add) {
      add(obj);
    }
    return *this;
  }


  Object get_active_tile() const {
    return Object(api()->tileview_get_tile_act(m_object));
  }

  TileView &set_tile(const Location &location) {
    api()->obj_set_tile_id(
      object(), location.column(), location.row(),
      static_cast<lv_anim_enable_t>(location.is_animate()));
    return *this;
  }

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_TILEVIEW_HPP
