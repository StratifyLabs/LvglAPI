#include "lvgl/Label.hpp"

using namespace lvgl;

Label::Label(Object parent, const Create& options){
  m_object = api()->label_create(parent.object());
  set_name(options.name());
}

Label::Label(Object parent, const Label&){
  m_object = api()->label_create(parent.object());
}
