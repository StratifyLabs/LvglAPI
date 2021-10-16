#ifndef LVGLAPI_LVGL_BUTTONMATRIX_HPP
#define LVGLAPI_LVGL_BUTTONMATRIX_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class ButtonMatrix : public ObjectAccess<ButtonMatrix> {
public:

  explicit ButtonMatrix(const char * name) : ObjectAccess(name){}
  explicit ButtonMatrix(const UserData & context) : ObjectAccess(context.cast_as_name()){}

  static const lv_obj_class_t * get_class(){
    return api()->button_matrix_class;
  }

  u16 get_selected_button() const { return api()->btnmatrix_get_selected_btn(object()); }

  const char *get_button_text(u16 id) const {
    return api()->btnmatrix_get_btn_text(object(), id);
  }

  const char *get_selected_text() const { return get_button_text(get_selected_button()); }

private:
  OBJECT_ACCESS_FRIENDS();
  friend class Keyboard;
  friend class TabView;
  friend class MessageBox;
  explicit ButtonMatrix(lv_obj_t *obj){ m_object = obj; }
  explicit ButtonMatrix(lv_btnmatrix_t *matrix){ m_object = reinterpret_cast<lv_obj_t*>(matrix); }

  ButtonMatrix(Object parent, const ButtonMatrix &);

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_BUTTONMATRIX_HPP
