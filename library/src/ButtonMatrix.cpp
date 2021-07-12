#include "lvgl/ButtonMatrix.hpp"

using namespace lvgl;

ButtonMatrix::ButtonMatrix(Object parent, const Create& options): ObjectAccess(object_type()){
  m_object = api()->btnmatrix_create(parent.object());
  set_name(options.name());
}
