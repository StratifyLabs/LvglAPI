#include "lvgl/Table.hpp"

using namespace lvgl;

Table::Table(const char * name){
  m_object = api()->table_create(screen_object());
  set_user_data(m_object,name);
}
