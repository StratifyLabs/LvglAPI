#include "lvgl/TextArea.hpp"

using namespace lvgl;

TextArea::TextArea(Object parent, const TextArea&){
  m_object = api()->textarea_create(parent.object());
}
