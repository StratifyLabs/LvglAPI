#ifndef LVGLAPI_LVGL_SPINNER_HPP
#define LVGLAPI_LVGL_SPINNER_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Spinner : public ObjectAccess<Spinner> {
public:
  struct Construct {
    API_PUBLIC_MEMBER(Construct, const char *, name, "");
    API_PUBLIC_MEMBER(Construct, u32, time, 1000);
    API_PUBLIC_MEMBER(Construct, u32, arc_length, 60);
  };

  explicit Spinner(const Construct &options);

  static const lv_obj_class_t *get_class() { return api()->spinner_class; }

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Spinner(lv_obj_t *object) { m_object = object; }

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_SPINNER_HPP
