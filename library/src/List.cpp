#include "lvgl/List.hpp"

using namespace lvgl;

List::List(Object parent, const Create& options){
  m_object = api()->list_create(parent.object());
  set_name(options.name());
}


List::List(Object parent, const List&){
  m_object = api()->list_create(parent.object());
}
