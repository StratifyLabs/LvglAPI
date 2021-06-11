#include "lvgl/Image.hpp"

using namespace lv;

Image::Image(Object parent, const Create& options){
  m_object = api()->img_create(parent.object());
  set_name(options.name());
}
