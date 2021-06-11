#include "lvgl/Table.hpp"

using namespace lv;

Table::Table(Object parent, const Create & options){
  m_object = api()->table_create(parent.object());
  set_name(options.name());
}
