#include "lvgl/Image.hpp"

using namespace lvgl;

Image::Image(Object parent, const Create& options): ObjectAccess(object_type()){
  m_object = api()->img_create(parent.object());
  set_name(options.name());
}
