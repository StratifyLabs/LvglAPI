#ifndef LVGLAPI_LVGL_CONTAINER_HPP
#define LVGLAPI_LVGL_CONTAINER_HPP

#include <var/StringView.hpp>

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Container : public ObjectAccess<Container> {
public:
  explicit Container(const char *name) : ObjectAccess(name) {}
  explicit Container(const UserData &context) : ObjectAccess(context.cast_as_name()) {}

  static Container active_screen() {
    Container result(Api::api()->disp_get_scr_act(nullptr));
    return result;
  }

  Container(lv_obj_t *object) { m_object = object; }
  Container(Object &object) { m_object = object.object(); }

private:
  OBJECT_ACCESS_FRIENDS();
  Container(Object parent, const Container &) {
    m_object = api()->obj_create(parent.object());
  }
};

class NakedContainer : public ObjectAccess<NakedContainer> {
public:
  explicit NakedContainer(const char *name) : ObjectAccess(name) {}
  explicit NakedContainer(const UserData &context)
    : ObjectAccess(context.cast_as_name()) {}

private:
  OBJECT_ACCESS_FRIENDS();
  NakedContainer(Object parent, const NakedContainer &) {
    m_object = api()->label_create(parent.object());
    api()->label_set_text_static(m_object, "");
  }
};

class Row : public ObjectAccess<Row> {
public:
  explicit Row(const char *name) : ObjectAccess(name) {}
  explicit Row(const UserData &context) : ObjectAccess(context.cast_as_name()) {}

private:
  OBJECT_ACCESS_FRIENDS();
  Row(Object parent, const Row &) {
    m_object = api()->label_create(parent.object());
    api()->label_set_text_static(m_object, "");
    set_flex_layout()
      .set_flex_flow(FlexFlow::row)
      .set_flex_align(SetFlexAlign().set_main(FlexAlign::start))
      .set_row_padding(20);
  }
};

class Column : public ObjectAccess<Column> {
public:
  explicit Column(const char *name) : ObjectAccess(name) {}
  explicit Column(const UserData &context) : ObjectAccess(context.cast_as_name()) {}

private:
  OBJECT_ACCESS_FRIENDS();
  Column(Object parent, const Column &) {
    m_object = api()->label_create(parent.object());
    api()->label_set_text_static(m_object, "");
    set_flex_layout()
      .set_flex_flow(FlexFlow::column)
      .set_flex_align(SetFlexAlign().set_main(FlexAlign::start))
      .set_column_padding(20);
  }
};


inline Container screen() {
  Container result(Api::api()->disp_get_scr_act(nullptr));
  return result;
}

} // namespace lvgl

#endif // LVGLAPI_LVGL_CONTAINER_HPP
