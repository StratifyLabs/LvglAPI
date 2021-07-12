#include "lvgl/Table.hpp"

using namespace lvgl;

Table::Table(Object parent, const Create & options): ObjectAccess(object_type()){
  m_object = api()->table_create(parent.object());
  set_name(options.name());
}
