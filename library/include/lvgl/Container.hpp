#ifndef LVGLAPI_LVGL_CONTAINER_HPP
#define LVGLAPI_LVGL_CONTAINER_HPP

#include <var/StringView.hpp>

#include "ObjectAccess.hpp"

namespace lvgl {

class Container : public ObjectAccess<Container> {
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char *name) : CreateAccess(name) {}
  };

  Container(Object parent, const Create &options)
    : ObjectAccess(object_type()) {
    m_object = api()->label_create(parent.object());
    api()->label_set_text(m_object, "");
    set_name(options.name());
  }

  Container(const char *name) : ObjectAccess(object_type()) {
    m_object = api()->obj_create(lv_scr_act());
    set_name(name);
  }

  Container(lv_obj_t *object) : ObjectAccess(object_type()) { m_object = object; }

  static Container active_screen() {
    Container result(Api::api()->disp_get_scr_act(nullptr));
    return result;
  }

private:
};



} // namespace lvgl

#endif // LVGLAPI_LVGL_CONTAINER_HPP
