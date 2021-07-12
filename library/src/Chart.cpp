#include "lvgl/Chart.hpp"

using namespace lvgl;

Chart::Chart(Object parent, const Create & options): ObjectAccess(object_type()){
  m_object = api()->chart_create(parent.object());
  set_name(options.name());
}
