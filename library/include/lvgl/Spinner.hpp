#ifndef LVGLAPI_LVGL_SPINNER_HPP
#define LVGLAPI_LVGL_SPINNER_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Spinner : public ObjectAccess<Spinner> {
public:
  class Construct {
    API_AF(Construct, u32, time, 1000);
    API_AF(Construct, u32, arc_length, 60);
  };

  explicit Spinner(const char *name, const Construct &options)
    : ObjectAccess(name), m_construct(&options) {}
  explicit Spinner(const Context &context, const Construct &options)
    : ObjectAccess(context.cast_as_name()), m_construct(&options) {}

  static const lv_obj_class_t *get_object_class() { return api()->spinner_class; }

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Spinner(lv_obj_t *object) { m_object = object; }
  Spinner(Object parent, const Spinner &options);

  const Construct *m_construct = nullptr;
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_SPINNER_HPP
