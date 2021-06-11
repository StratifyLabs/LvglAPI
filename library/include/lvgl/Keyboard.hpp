#ifndef LVGLAPI_LVGL_KEYBOARD_HPP
#define LVGLAPI_LVGL_KEYBOARD_HPP

#include "Object.hpp"

namespace lv {

class Keyboard : public ObjectAccess<Keyboard>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  Keyboard();
};

}

#endif // LVGLAPI_LVGL_KEYBOARD_HPP
