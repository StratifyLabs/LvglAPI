#ifndef LVGLAPI_LVGL_CONTAINER_HPP
#define LVGLAPI_LVGL_CONTAINER_HPP

#include <var/StringView.hpp>

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Container : public ObjectAccess<Container> {
public:
  Container(const char *name) : ObjectAccess(name) {}

  static Container active_screen() {
    Container result(Api::api()->disp_get_scr_act(nullptr));
    return result;
  }

  //living dangerously
  Container(lv_obj_t *object) { m_object = object; }

private:
  OBJECT_ACCESS_FRIENDS();

  Container(Object parent, const Container &options) : ObjectAccess(object_type()) {
    if (options.is_initial_bordered()) {
      m_object = api()->obj_create(parent.object());
    } else {
      m_object = api()->label_create(parent.object());
      api()->label_set_text(m_object, "");
    }
  }

  API_AB(Container, initial_bordered, false);
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_CONTAINER_HPP
