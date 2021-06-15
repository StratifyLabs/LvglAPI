#include "lvgl/Chart.hpp"

using namespace lv;

Chart::Chart(Object parent, const Create & options){
  m_object = api()->chart_create(parent.object());
  set_name(options.name());
}
