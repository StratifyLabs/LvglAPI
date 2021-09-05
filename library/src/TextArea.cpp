#include "lvgl/TextArea.hpp"

using namespace lvgl;

TextArea::TextArea(Object parent, const Create& options){
  m_object = api()->textarea_create(parent.object());
  set_name(options.name());
}

TextArea::TextArea(Object parent, const TextArea&){
  m_object = api()->textarea_create(parent.object());
}
