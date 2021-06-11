#include "lvgl/ButtonMatrix.hpp"

using namespace lv;

ButtonMatrix::ButtonMatrix(Object parent, const Create& options){
  m_object = api()->btnmatrix_create(parent.object());
  set_name(options.name());
}
