#include "lvgl/Image.hpp"

using namespace lv;

Image::Image(Object& parent){
  m_object = api()->img_create(parent.object());
}
