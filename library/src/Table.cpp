#include "lvgl/Table.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(Table);

Table::Table(const char * name){
  m_object = api()->table_create(screen_object());
  set_user_data(m_object,name);
}
