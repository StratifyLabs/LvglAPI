#ifndef LVGLAPI_LVGL_BUTTON_HPP
#define LVGLAPI_LVGL_BUTTON_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Button : public ObjectAccess<Button> {
public:

  explicit Button(const char * name) : ObjectAccess(name){}

private:
  OBJECT_ACCESS_FRIENDS();
  friend class List;
  friend class Window;
  friend class TabView;
  Button(lv_obj_t * object){ m_object = object; }
  Button(Object parent, const Button &);

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_BUTTON_HPP
