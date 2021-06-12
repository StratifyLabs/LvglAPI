#ifndef LVGLAPI_LVGL_LIST_HPP
#define LVGLAPI_LVGL_LIST_HPP

#include "Object.hpp"

namespace lv {

class List : public ObjectAccess<List>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  List(Object parent, const Create & options);


  List & add_button(const char * symbol, const char * text){
    api()->list_add_btn(m_object, symbol, text);
    return *this;
  }

  List & add_text(const char * text){
    api()->list_add_text(m_object, text);
    return *this;
  }

};




}

#endif // LVGLAPI_LVGL_LIST_HPP
