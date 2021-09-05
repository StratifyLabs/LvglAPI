#include "lvgl/Label.hpp"

using namespace lvgl;

Label::Label(Object parent, const Label&){
  m_object = api()->label_create(parent.object());
}
