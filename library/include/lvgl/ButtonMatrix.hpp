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

  u16 get_selected_button() const {
    return api()->btnmatrix_get_selected_btn(object());
  }

  const char * get_button_text(u16 id) const {
    return api()->btnmatrix_get_btn_text(object(), id);
  }

  const char * get_selected_text() const {
    return get_button_text(get_selected_button());
  }
};

} // namespace lv

#endif // LVGLAPI_LVGL_BUTTONMATRIX_HPP
