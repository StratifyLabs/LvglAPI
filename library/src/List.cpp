#include "lvgl/List.hpp"

using namespace lvgl;


List::List(Object parent, const List&){
  m_object = api()->list_create(parent.object());
}
