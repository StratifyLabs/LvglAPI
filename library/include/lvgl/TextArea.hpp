#ifndef LVGLAPI_LVGL_TEXTAREA_HPP
#define LVGLAPI_LVGL_TEXTAREA_HPP

#include "Object.hpp"

namespace lv {

class TextArea : public ObjectAccess<TextArea>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  TextArea(Object parent, const Create & options);

  TextArea & set_password_mode(bool value = true){
    api()->textarea_set_password_mode(object(), value);
    return *this;
  }


  TextArea & set_one_line_mode(bool value = true){
    api()->textarea_set_one_line(object(), value);
    return *this;
  }


private:
  friend class Keyboard;
  TextArea(lv_obj_t * obj){
    m_object = obj;
  }
};

}

#endif // LVGLAPI_LVGL_TEXTAREA_HPP
