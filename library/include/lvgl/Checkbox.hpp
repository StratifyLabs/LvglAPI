#ifndef LVGLAPI_LVGL_CHECKBOX_HPP
#define LVGLAPI_LVGL_CHECKBOX_HPP

#include "ObjectAccess.hpp"

namespace lvgl {


class Checkbox : public ObjectAccess<Checkbox>{
public:

  explicit Checkbox(const char * name);
  explicit Checkbox(lv_obj_t * object){ m_object = object; }

  static const lv_obj_class_t * get_class(){
    return api()->checkbox_class;
  }

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

};

}

#endif // LVGLAPI_LVGL_CHECKBOX_HPP
