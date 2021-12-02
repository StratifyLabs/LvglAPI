#include "lvgl/List.hpp"
#include "lvgl/Event.hpp"

using namespace lvgl;

List::List(const char * name) {
  m_object = api()->list_create(screen_object());
  set_user_data(m_object,name);
}


