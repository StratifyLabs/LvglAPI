#ifndef LVGLAPI_LVGL_MESSAGEBOX_HPP
#define LVGLAPI_LVGL_MESSAGEBOX_HPP

#include "ObjectAccess.hpp"

namespace lvgl {

class MessageBox  : public ObjectAccess<MessageBox> {
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  MessageBox(Object parent, const Create & options);
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_MESSAGEBOX_HPP
