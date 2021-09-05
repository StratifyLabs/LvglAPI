#include "lvgl/ButtonMatrix.hpp"

using namespace lvgl;

ButtonMatrix::ButtonMatrix(Object parent, const Create& options){
  m_object = api()->btnmatrix_create(parent.object());
  set_name(options.name());
}

ButtonMatrix::ButtonMatrix(Object parent, const ButtonMatrix&){
  m_object = api()->btnmatrix_create(parent.object());
}
