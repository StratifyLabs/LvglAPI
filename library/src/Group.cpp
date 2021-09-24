#include "lvgl/Group.hpp"


using namespace lvgl;

Group Group::create() {
  Group result;
  result.m_group = api()->group_create();
  return result;
}
