#include "lvgl/Chart.hpp"

using namespace lvgl;

Chart::Chart(Object parent, const Create & options){
  m_object = api()->chart_create(parent.object());
  set_name(options.name());
}

Chart::Chart(Object parent, const Chart &){
  m_object = api()->chart_create(parent.object());
}
