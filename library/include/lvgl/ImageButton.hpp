#ifndef LVGLAPI_LVGL_IMAGEBUTTON_HPP
#define LVGLAPI_LVGL_IMAGEBUTTON_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class ImageButton : public ObjectAccess<ImageButton>
{
public:
  explicit ImageButton(const char * name) : ObjectAccess(name){}
  explicit ImageButton(const UserData & context) : ObjectAccess(context.cast_as_name()){}


  static const lv_obj_class_t * get_class(){
    return api()->image_button_class;
  }

private:
  OBJECT_ACCESS_FRIENDS();
  explicit ImageButton(lv_obj_t * object){ m_object = object; }
  ImageButton(Object parent, const ImageButton&);
};

}

#endif // LVGLAPI_LVGL_IMAGEBUTTON_HPP
