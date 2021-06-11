#ifndef LVGLAPI_LVGL_MESSAGEBOX_HPP
#define LVGLAPI_LVGL_MESSAGEBOX_HPP

#include "Object.hpp"

namespace lv {

class MessageBox  : public ObjectAccess<MessageBox> {
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  MessageBox(Object parent, const Create & options);
};

} // namespace lv

#endif // LVGLAPI_LVGL_MESSAGEBOX_HPP
