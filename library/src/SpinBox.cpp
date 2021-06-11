#include "lvgl/Spinbox.hpp"

using namespace lv;

SpinBox::SpinBox(Object parent, const Create & options){
  //m_object = api()->spinbox_create(parent.object());
  set_name(options.name());
}
