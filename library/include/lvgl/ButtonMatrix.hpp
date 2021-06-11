#ifndef LVGLAPI_LVGL_BUTTONMATRIX_HPP
#define LVGLAPI_LVGL_BUTTONMATRIX_HPP

#include "Object.hpp"

namespace lv {
class ButtonMatrix : public ObjectAccess<ButtonMatrix> {
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };

  explicit ButtonMatrix(lv_obj_t * obj){
    m_object = obj;
  }
  ButtonMatrix(Object parent, const Create & options);
};

} // namespace lv

#endif // LVGLAPI_LVGL_BUTTONMATRIX_HPP
