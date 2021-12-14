#ifndef LVGLAPI_LVGL_CHECKBOX_HPP
#define LVGLAPI_LVGL_CHECKBOX_HPP

#include "ObjectAccess.hpp"

namespace lvgl {


class CheckBox : public ObjectAccess<CheckBox>{
public:

  explicit CheckBox(const char * name = "");
  explicit CheckBox(lv_obj_t * object){ m_object = object; }

  static const lv_obj_class_t * get_class(){
    return api()->checkbox_class;
  }

  CheckBox & set_text(const char * text){
    api()->checkbox_set_text(object(), text);
    return *this;
  }

  CheckBox & set_text_static(const char * text){
    api()->checkbox_set_text_static(object(), text);
    return *this;
  }

  API_NO_DISCARD const char * get_text() const {
    return api()->checkbox_get_text(object());
  }

};

}

#endif // LVGLAPI_LVGL_CHECKBOX_HPP
