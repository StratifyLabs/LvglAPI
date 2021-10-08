#ifndef LVGLAPI_LVGL_BUTTON_HPP
#define LVGLAPI_LVGL_BUTTON_HPP

#include "Label.hpp"
#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Button : public ObjectAccess<Button> {
public:
  explicit Button(const char *name) : ObjectAccess(name) {}
  explicit Button(const Context &context) : ObjectAccess(context.cast_as_name()) {}

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

  class LabelContext : public Context {
  public:
    LabelContext(const char * name = "") : Context(name){}
  private:
    API_AF(LabelContext, Alignment, alignment, Alignment::center);
    API_AF(LabelContext, u8, right_padding, 0);
    API_AF(LabelContext, u8, left_padding, 0);
  };

  Button &add_label(const LabelContext &context) {
    return add(Label(context).configure([](Label &label) {
      const var::StringView name = label.name();
      const auto *context = label.context<LabelContext>();
      label.set_alignment(context->alignment())
        .set_left_padding(context->left_padding())
        .set_right_padding(context->right_padding())
        .set_text(name.is_empty() ? label.get_parent().name() : label.name());
    }));
  }

private:
  OBJECT_ACCESS_FRIENDS();
  friend class List;
  friend class Window;
  friend class TabView;
  Button(lv_obj_t *object) { m_object = object; }
  Button(Object parent, const Button &);
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_BUTTON_HPP
