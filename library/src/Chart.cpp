#include "lvgl/Chart.hpp"

using namespace lvgl;

Chart::Chart(Object parent, const Chart &){
  m_object = api()->chart_create(parent.object());
}
