#ifndef LVGLAPI_LVGL_CHECKBOX_HPP
#define LVGLAPI_LVGL_CHECKBOX_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Checkbox : public ObjectAccess<Checkbox>{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };

  explicit Checkbox(const char * name) : ObjectAccess(name){}

  Checkbox & set_text(const char * text){
    api()->checkbox_set_text(object(), text);
    return *this;
  }

  Checkbox & set_static_text(const char * text){
    api()->checkbox_set_text_static(object(), text);
    return *this;
  }

  const char * get_text() const {
    return api()->checkbox_get_text(object());
  }

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Checkbox(lv_obj_t * object){ m_object = object; }
  Checkbox(Object parent, const Checkbox &);
  Checkbox(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_CHECKBOX_HPP
