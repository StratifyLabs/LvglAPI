#include "lvgl/Label.hpp"

using namespace lv;

Label::Label(Object & parent){
  m_object = api()->label_create(parent.object());
}
