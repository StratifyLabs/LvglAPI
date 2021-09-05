#include "lvgl/Table.hpp"

using namespace lvgl;

Table::Table(Object parent, const Create & options){
  m_object = api()->table_create(parent.object());
  set_name(options.name());
}


Table::Table(Object parent, const Table &){
  m_object = api()->table_create(parent.object());
}
