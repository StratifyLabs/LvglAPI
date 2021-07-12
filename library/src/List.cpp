#include "lvgl/List.hpp"

using namespace lvgl;

List::List(Object parent, const Create& options): ObjectAccess(object_type()){
  m_object = api()->list_create(parent.object());
  set_name(options.name());
}
