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
};

}

#endif // LVGLAPI_LVGL_TEXTAREA_HPP
