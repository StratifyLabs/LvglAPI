#ifndef LVGLAPI_LVGL_BUTTON_HPP
#define LVGLAPI_LVGL_BUTTON_HPP

#include "ObjectAccess.hpp"

namespace lvgl {

class Button : public ObjectAccess<Button> {
public:

  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };

  Button(Object parent, const Create & options): ObjectAccess(object_type()){
    m_object = api()->btn_create(parent.object());
    set_name(options.name());
  }

private:
  friend class Window;
  Button(lv_obj_t * object) : ObjectAccess(object_type()){
    m_object = object;
  }

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_BUTTON_HPP
