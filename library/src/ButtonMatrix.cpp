#include "lvgl/ButtonMatrix.hpp"

using namespace lvgl;

ButtonMatrix::ButtonMatrix(Object parent, const ButtonMatrix&){
  m_object = api()->btnmatrix_create(parent.object());
}
