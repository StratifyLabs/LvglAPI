#ifndef LVGLAPI_LVGL_BUTTON_HPP
#define LVGLAPI_LVGL_BUTTON_HPP

#include "Label.hpp"
#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Button : public ObjectAccess<Button> {
public:
  explicit Button(const char *name) : ObjectAccess(name) {}
  explicit Button(const UserData &context) : ObjectAccess(context.cast_as_name()) {}

  static const lv_obj_class_t * get_class(){
    return api()->button_class;
  }

  Button &add_label(const char *label_name = "") {
    return add(Label(label_name).configure([](Label &label) {
      const var::StringView name = label.name();
      label.set_alignment(Alignment::center)
        .set_text(name.is_empty() ? label.get_parent().name() : label.name());
    }));
  }

  class LabelUserData : public UserDataAccess<LabelUserData> {
  public:
    LabelUserData(const char * name = "") : UserDataBase(name){}
  private:
    API_AF(LabelUserData, Alignment, alignment, Alignment::center);
    API_AF(LabelUserData, u8, right_padding, 0);
    API_AF(LabelUserData, u8, left_padding, 0);
  };

  Button &add_label(const LabelUserData &user_data) {
    return add(Label(user_data).configure([](Label &label) {
      const var::StringView name = label.name();
      const auto *user_data = label.user_data<LabelUserData>();
      label.set_alignment(user_data->alignment())
        .set_left_padding(user_data->left_padding())
        .set_right_padding(user_data->right_padding())
        .set_text(name.is_empty() ? label.get_parent().name() : label.name());
    }));
  }

private:
  OBJECT_ACCESS_FRIENDS();
  friend class List;
  friend class Window;
  friend class TabView;
  friend class MessageBox;
  Button(lv_obj_t *object) { m_object = object; }
  Button(Object parent, const Button &);
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_BUTTON_HPP
