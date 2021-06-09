#ifndef LVGLAPI_LVGL_BUTTONMATRIX_HPP
#define LVGLAPI_LVGL_BUTTONMATRIX_HPP

#include "Object.hpp"

namespace lv {
class ButtonMatrix : public ObjectAccess<ButtonMatrix> {
public:
  explicit ButtonMatrix(lv_obj_t * obj){
    m_object = obj;
  }
  ButtonMatrix(Object parent);
};

} // namespace lv

#endif // LVGLAPI_LVGL_BUTTONMATRIX_HPP
