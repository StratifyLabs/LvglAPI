#ifndef LVGLAPI_LVGL_CONTAINER_HPP
#define LVGLAPI_LVGL_CONTAINER_HPP

#include <var/StringView.hpp>

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Container : public ObjectAccess<Container> {
public:
  explicit Container(const char *name) : ObjectAccess(name) {}
  explicit Container(const Context &context) : ObjectAccess(context.cast_as_name()) {}

  static Container active_screen() {
    Container result(Api::api()->disp_get_scr_act(nullptr));
    return result;
  }

  // living dangerously
  Container(lv_obj_t *object) { m_object = object; }
  Container(Object &object) { m_object = object.object(); }

private:
  OBJECT_ACCESS_FRIENDS();
  Container(Object parent, const Container &) {
    m_object = api()->obj_create(parent.object());
  }
};

class NakedContainer : public ObjectAccess<Container> {
public:
  explicit NakedContainer(const char *name) : ObjectAccess(name) {}
  explicit NakedContainer(const Context &context)
    : ObjectAccess(context.cast_as_name()) {}

private:
  OBJECT_ACCESS_FRIENDS();
  NakedContainer(Object parent, const NakedContainer &) {
    m_object = api()->label_create(parent.object());
    api()->label_set_text_static(m_object, "");
  }
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_CONTAINER_HPP
