#include "lvgl/ButtonMatrix.hpp"

using namespace lv;

ButtonMatrix::ButtonMatrix(Object parent){
  m_object = api()->btnmatrix_create(parent.object());
}
