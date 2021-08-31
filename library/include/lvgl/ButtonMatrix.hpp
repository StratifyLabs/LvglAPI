#ifndef LVGLAPI_LVGL_BUTTONMATRIX_HPP
#define LVGLAPI_LVGL_BUTTONMATRIX_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
class ButtonMatrix : public ObjectAccess<ButtonMatrix> {
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char *name) : CreateAccess(name) {}
  };

  explicit ButtonMatrix(lv_obj_t *obj) : ObjectAccess(object_type()) { m_object = obj; }

  ButtonMatrix(Object parent, const Create &options);

  u16 get_selected_button() const { return api()->btnmatrix_get_selected_btn(object()); }

  const char *get_button_text(u16 id) const {
    return api()->btnmatrix_get_btn_text(object(), id);
  }

  const char *get_selected_text() const { return get_button_text(get_selected_button()); }

private:
  friend class Keyboard;
  ButtonMatrix(lv_btnmatrix_t *matrix)
    : ObjectAccess<ButtonMatrix>(object_type()) { m_object = reinterpret_cast<lv_obj_t*>(matrix); }
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_BUTTONMATRIX_HPP
