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


private:
  friend class Keyboard;
  TextArea(lv_obj_t * obj){
    m_object = obj;
  }
};

}

#endif // LVGLAPI_LVGL_TEXTAREA_HPP
