#include "lvgl/Label.hpp"

using namespace lvgl;

Label::Label(Object parent, const Create& options): ObjectAccess(object_type()){
  m_object = api()->label_create(parent.object());
  set_name(options.name());
}
