#ifndef LVGLAPI_LVGL_SPINNER_HPP
#define LVGLAPI_LVGL_SPINNER_HPP

#include "ObjectAccess.hpp"

namespace lvgl {


class Spinner : public ObjectAccess<Spinner> {
public:
  struct Construct {
    //name is first
    API_PUBLIC_MEMBER(Construct, const char *, name, "");
    //alphabetical
    API_PUBLIC_MEMBER(Construct, u32, arc_length, 60);
    API_PUBLIC_MEMBER(Construct, u32, time, 1000);
  };

  explicit Spinner(const Construct &options);
  explicit Spinner(const char * name);
  explicit Spinner(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->spinner_class; }

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_SPINNER_HPP
