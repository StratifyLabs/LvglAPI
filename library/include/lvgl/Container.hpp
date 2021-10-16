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
  NakedContainer(lv_obj_t *object) { m_object = object; }
  NakedContainer(Object parent, const NakedContainer &) {
    m_object = api()->label_create(parent.object());
    api()->label_set_text_static(m_object, "");
  }
};

class Row : public ObjectAccess<Row> {
public:
  explicit Row(const char *name = "") : ObjectAccess(name) {}
  explicit Row(const UserData &context) : ObjectAccess(context.cast_as_name()) {}

  Row& justify_space_between(){
    return set_flex_align(SetFlexAlign().set_main(FlexAlign::space_between));
  }

  Row& justify_space_around(){
    return set_flex_align(SetFlexAlign().set_main(FlexAlign::space_around));
  }

  Row& justify_space_evenly(){
    return set_flex_align(SetFlexAlign().set_main(FlexAlign::space_evenly));
  }

  Row& justify_start(){
    return set_flex_align(SetFlexAlign().set_main(FlexAlign::start));
  }

  Row& justify_end(){
    return set_flex_align(SetFlexAlign().set_main(FlexAlign::end));
  }

private:
  OBJECT_ACCESS_FRIENDS();
  Row(lv_obj_t *object) { m_object = object; }
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
  explicit Column(const char *name = "") : ObjectAccess(name) {}
  explicit Column(const UserData &context) : ObjectAccess(context.cast_as_name()) {}

  Column& justify_space_between(){
    return set_flex_align(SetFlexAlign().set_main(FlexAlign::space_between));
  }

  Column& justify_space_around(){
    return set_flex_align(SetFlexAlign().set_main(FlexAlign::space_around));
  }

  Column& justify_space_evenly(){
    return set_flex_align(SetFlexAlign().set_main(FlexAlign::space_evenly));
  }

private:
  OBJECT_ACCESS_FRIENDS();
  Column(lv_obj_t *object) { m_object = object; }
  Column(Object parent, const Column &) {
    m_object = api()->label_create(parent.object());
    api()->label_set_text_static(m_object, "");
    set_flex_layout()
      .set_flex_flow(FlexFlow::column)
      .set_flex_align(SetFlexAlign().set_main(FlexAlign::start))
      .set_column_padding(20);
  }
};

class ColumnSpacer : public ObjectAccess<ColumnSpacer> {
public:
  ColumnSpacer(lv_coord_t height = 50) : ObjectAccess(""), m_construct_height(height) {}

private:
  OBJECT_ACCESS_FRIENDS();

  lv_coord_t m_construct_height = 50;

  ColumnSpacer(Object &parent, const ColumnSpacer &options) {
    m_object = api()->label_create(parent.object());
    api()->label_set_text_static(m_object, "");

    fill_width().set_height(options.m_construct_height);
  }
};

class RowSpacer : public ObjectAccess<RowSpacer> {
public:
  RowSpacer(lv_coord_t width = 30) : ObjectAccess(""), m_construct_width(width) {}

private:
  OBJECT_ACCESS_FRIENDS();

  lv_coord_t m_construct_width = 30;

  RowSpacer(Object &parent, const RowSpacer &options) {
    m_object = api()->label_create(parent.object());
    api()->label_set_text_static(m_object, "");
    fill_height().set_width(options.m_construct_width);
  }
};

inline Container screen() {
  Container result(Api::api()->disp_get_scr_act(nullptr));
  return result;
}

} // namespace lvgl

#endif // LVGLAPI_LVGL_CONTAINER_HPP
