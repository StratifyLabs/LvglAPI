#ifndef LVGLAPI_LVGL_CONTAINER_HPP
#define LVGLAPI_LVGL_CONTAINER_HPP

#include <var/StringView.hpp>

#include "ObjectAccess.hpp"

namespace lvgl {


class Container : public ObjectAccess<Container> {
public:
  explicit Container(const char *name) {
    m_object = api()->obj_create(screen_object());
    set_user_data(m_object, name);
  }

  static Container active_screen() {
    Container result(Api::api()->disp_get_scr_act(nullptr));
    return result;
  }

  Container(lv_obj_t *object) { m_object = object; }
  Container(Object &object) { m_object = object.object(); }

};

class NakedContainer : public ObjectAccess<NakedContainer> {
public:
  explicit NakedContainer(const char *name) {
    m_object = api()->label_create(screen_object());
    api()->label_set_text_static(m_object, "");
    set_user_data(m_object, name);
  }
  NakedContainer(lv_obj_t *object) { m_object = object; }
};

class Row : public ObjectAccess<Row> {
public:
  explicit Row(const char *name = "") {
    m_object = api()->label_create(screen_object());
    api()->label_set_text_static(m_object, "");
    set_user_data(m_object, name);
    set_flex_layout()
      .set_flex_flow(FlexFlow::row)
      .set_flex_align(SetFlexAlign().set_main(FlexAlign::start))
      .set_row_padding(20);
  }
  Row(lv_obj_t *object) { m_object = object; }

  Row &justify_space_between() {
    return set_flex_align(SetFlexAlign().set_main(FlexAlign::space_between));
  }

  Row &justify_space_around() {
    return set_flex_align(SetFlexAlign().set_main(FlexAlign::space_around));
  }

  Row &justify_space_evenly() {
    return set_flex_align(SetFlexAlign().set_main(FlexAlign::space_evenly));
  }

  Row &justify_start() {
    return set_flex_align(SetFlexAlign().set_main(FlexAlign::start));
  }

  Row &justify_end() { return set_flex_align(SetFlexAlign().set_main(FlexAlign::end)); }

};

class Column : public ObjectAccess<Column> {
public:
  explicit Column(const char *name = "") {
    m_object = api()->label_create(screen_object());
    api()->label_set_text_static(m_object, "");
    set_user_data(m_object, name);
    set_flex_layout()
      .set_flex_flow(FlexFlow::column)
      .set_flex_align(SetFlexAlign().set_main(FlexAlign::start))
      .set_column_padding(20);
  }
  Column(lv_obj_t *object) { m_object = object; }

  Column &justify_space_between() {
    return set_flex_align(SetFlexAlign().set_main(FlexAlign::space_between));
  }

  Column &justify_space_around() {
    return set_flex_align(SetFlexAlign().set_main(FlexAlign::space_around));
  }

  Column &justify_space_evenly() {
    return set_flex_align(SetFlexAlign().set_main(FlexAlign::space_evenly));
  }

};

class ColumnSpacer : public ObjectAccess<ColumnSpacer> {
public:
  ColumnSpacer(const char *name = "", lv_coord_t height = 50) { construct(name, height); }
  ColumnSpacer(lv_coord_t height) { construct("", height); }
  ColumnSpacer(lv_obj_t *object) { m_object = object; }

  lv_coord_t m_construct_height = 50;

  void construct(const char *name, lv_coord_t height) {
    m_object = api()->label_create(Api::api()->disp_get_scr_act(nullptr));
    set_user_data(m_object, name);
    api()->label_set_text_static(m_object, "");
    fill_width().set_height(height);
  }
};

class RowSpacer : public ObjectAccess<RowSpacer> {
public:
  RowSpacer(const char *name = "", lv_coord_t width = 50) { construct(name, width); }
  RowSpacer(lv_coord_t width) { construct("", width); }
  RowSpacer(lv_obj_t *object) { m_object = object; }

  lv_coord_t m_construct_height = 50;

  void construct(const char *name, lv_coord_t width) {
    m_object = api()->label_create(Api::api()->disp_get_scr_act(nullptr));
    set_user_data(m_object, name);
    api()->label_set_text_static(m_object, "");
    fill_height().set_width(width);
  }
};

inline Container screen() {
  Container result(Api::api()->disp_get_scr_act(nullptr));
  return result;
}

} // namespace lvgl

#endif // LVGLAPI_LVGL_CONTAINER_HPP
