#include "lvgl/Page.hpp"

using namespace lv;

Page::Page(Object parent, const Create & options){

  set_name(options.name());
}
