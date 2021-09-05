#include "lvgl/Table.hpp"

using namespace lvgl;

Table::Table(Object parent, const Table &){
  m_object = api()->table_create(parent.object());
}
