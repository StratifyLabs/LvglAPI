#include "lvgl/Image.hpp"

using namespace lvgl;

Image::Image(Object parent, const Create& options){
  m_object = api()->img_create(parent.object());
  set_name(options.name());
}

Image::Image(Object parent, const Image&){
  m_object = api()->img_create(parent.object());
}
