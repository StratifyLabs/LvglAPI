#include "lvgl/Image.hpp"

using namespace lvgl;


Image::Image(Object parent, const Image&){
  m_object = api()->img_create(parent.object());
}
