#include "lvgl/Label.hpp"

using namespace lv;

Label::Label(Object parent, const Create& options){
  m_object = api()->label_create(parent.object());
  set_name(options.name());
}
