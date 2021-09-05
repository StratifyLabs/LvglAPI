#ifndef LVGLAPI_LVGL_MESSAGEBOX_HPP
#define LVGLAPI_LVGL_MESSAGEBOX_HPP

#include "ObjectAccess.hpp"
#include "Label.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class MessageBox  : public ObjectAccess<MessageBox> {
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}

    Create& set_button_list(const char * list[]){
      m_button_list = list;
      return *this;
    }

    const char ** button_list() const {
      return m_button_list;
    }

  private:
    API_AF(Create,const char*, title, "");
    API_AF(Create,const char*, message, "");
    API_AB(Create,add_close_button,true);

    const char ** m_button_list = nullptr;
  };

  explicit MessageBox(const char * name) : ObjectAccess(name){}

  const char * get_active_button_text() const {
    return api()->msgbox_get_active_btn_text(m_object);
  }

  Label get_text() const {
    return Label(api()->msgbox_get_text(m_object));
  }

  void close(){
    api()->msgbox_close(object());
  }


  //only used during construction
  MessageBox& set_initial_button_list(const char * list[]){
    API_ASSERT(m_object == nullptr);
    m_button_list = list;
    return *this;
  }

private:
  OBJECT_ACCESS_FRIENDS();
  explicit MessageBox(lv_obj_t * object){ m_object = object; }
  MessageBox(Object parent, const MessageBox & options);
  MessageBox(Object parent, const Create & options);

  API_AF(MessageBox,const char*, initial_title, "");
  API_AF(MessageBox,const char*, initial_message, "");
  API_AB(MessageBox,initial_add_close_button,true);
  API_AB(MessageBox, initial_modal, false);

  const char ** m_button_list = nullptr;

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_MESSAGEBOX_HPP
