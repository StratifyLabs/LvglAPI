#ifndef LVGLAPI_LVGL_LIST_HPP
#define LVGLAPI_LVGL_LIST_HPP

#include "ObjectAccess.hpp"

namespace lvgl {

class List : public ObjectAccess<List>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  List(Object parent, const Create & options);


  List & add_button(const char * symbol, const char * text){
    auto object = api()->list_add_btn(m_object, symbol, text);
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    object->user_data = nullptr;
    return *this;
  }

  List & add_button(const char * name, const char * symbol, const char * text){
    auto object = api()->list_add_btn(m_object, symbol, text);
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    object->user_data = (void*)name;
    return *this;
  }

  List & add_text(const char * text){
    auto object = api()->list_add_text(m_object, text);
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    object->user_data = nullptr;
    return *this;
  }

  List & add_text(const char * name, const char * text){
    auto object = api()->list_add_text(m_object, text);
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    object->user_data = (void*)name;
    return *this;
  }

  const char * get_button_text(Object button){
    return api()->list_get_btn_text(object(), button.object());
  }

};




}

#endif // LVGLAPI_LVGL_LIST_HPP
