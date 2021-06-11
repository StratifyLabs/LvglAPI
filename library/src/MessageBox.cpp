#include "lvgl/MessageBox.hpp"

using namespace lv;

MessageBox::MessageBox(Object parent, const Create& options){

  set_name(options.name());
}
