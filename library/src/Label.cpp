#include "lvgl/Generic.hpp"
#include "lvgl/Label.hpp"

using namespace lvgl;

Label::Label(const char * name){
  m_object = api()->label_create(screen().object());
  set_user_data(m_object, name);
  Label(m_object).set_text_static("");
}
