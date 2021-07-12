#include "lvgl/TextArea.hpp"

using namespace lvgl;

TextArea::TextArea(Object parent, const Create& options): ObjectAccess(object_type()){
  m_object = api()->textarea_create(parent.object());
  set_name(options.name());
}
