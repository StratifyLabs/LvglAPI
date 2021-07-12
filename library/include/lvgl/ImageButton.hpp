#ifndef LVGLAPI_LVGL_IMAGEBUTTON_HPP
#define LVGLAPI_LVGL_IMAGEBUTTON_HPP

#include "ObjectAccess.hpp"

namespace lvgl {

class ImageButton : public ObjectAccess<ImageButton>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  ImageButton();
};

}

#endif // LVGLAPI_LVGL_IMAGEBUTTON_HPP
