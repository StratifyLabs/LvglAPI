#include "lvgl/TextArea.hpp"

using namespace lv;

TextArea::TextArea(Object parent, const Create& options){
  m_object = api()->textarea_create(parent.object());
  set_name(options.name());
}
