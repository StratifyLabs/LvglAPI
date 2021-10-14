#include "lvgl/Label.hpp"

using namespace lvgl;

Label::Label(Object parent, const Label& options){
  m_object = api()->label_create(parent.object());
  api()->label_set_text_static(m_object, options.initial_name());
}
