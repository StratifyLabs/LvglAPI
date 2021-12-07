#ifndef LVGLAPI_LVGL_GENERIC_HPP
#define LVGLAPI_LVGL_GENERIC_HPP

#include <var/StringView.hpp>

#include "ObjectAccess.hpp"

namespace lvgl {

class Generic : public ObjectAccess<Generic> {
public:
  explicit Generic(lv_obj_t *object) { m_object = object; }
  explicit Generic(Object &object) { m_object = object.object(); }
};

inline Generic screen() {
  Generic result(Api::api()->disp_get_scr_act(nullptr));
  return result;
}

} // namespace lvgl

#endif // LVGLAPI_LVGL_GENERIC_HPP
