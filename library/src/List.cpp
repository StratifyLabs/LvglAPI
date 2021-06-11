#include "lvgl/List.hpp"

using namespace lv;

List::List(Object parent, const Create& options){
  m_object = api()->list_create(parent.object());
  set_name(options.name());
}
