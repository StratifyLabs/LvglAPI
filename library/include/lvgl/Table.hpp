#ifndef LVGLAPI_LVGL_TABLE_HPP
#define LVGLAPI_LVGL_TABLE_HPP

#include "ObjectAccess.hpp"

namespace lvgl {


class Table : public ObjectAccess<Table> {
public:
  enum class Control {
    merge_right = LV_TABLE_CELL_CTRL_MERGE_RIGHT,
    crop = LV_TABLE_CELL_CTRL_TEXT_CROP,
    custom1 = LV_TABLE_CELL_CTRL_CUSTOM_1,
    custom2 = LV_TABLE_CELL_CTRL_CUSTOM_2,
    custom3 = LV_TABLE_CELL_CTRL_CUSTOM_3,
    custom4 = LV_TABLE_CELL_CTRL_CUSTOM_4,
  };

  explicit Table(const char * name = "");
  explicit Table(lv_obj_t * object){ m_object = object; }

  static const lv_obj_class_t * get_class(){
    return api()->table_class;
  }

  class Cell {
    API_AF(Cell, u16, row, 0);
    API_AF(Cell, u16, column, 0);
  };

  Table &set_cell_value(const Cell &cell, const char *text) {
    api()->table_set_cell_value(object(), cell.row(), cell.column(), text);
    return *this;
  }

  Table &set_row_count(u16 value) {
    api()->table_set_row_cnt(object(), value);
    return *this;
  }

  Table &set_column_count(u16 value) {
    api()->table_set_col_cnt(object(), value);
    return *this;
  }

  Table &set_column_width(u16 column, lv_coord_t value) {
    api()->table_set_col_width(object(), column, value);
    return *this;
  }

  Table &add_cell_control(const Cell &cell, Control value) {
    api()->table_add_cell_ctrl(
      object(), cell.row(), cell.column(), static_cast<lv_table_cell_ctrl_t>(value));
    return *this;
  }

  Table &clear_cell_control(const Cell &cell, Control value) {
    api()->table_clear_cell_ctrl(
      object(), cell.row(), cell.column(), static_cast<lv_table_cell_ctrl_t>(value));
    return *this;
  }

  bool cell_has_control(const Cell &cell, Control value) {
    return api()->table_has_cell_ctrl(
      m_object, cell.row(), cell.column(), static_cast<lv_table_cell_ctrl_t>(value));
  }

  const char *get_cell_value(const Cell &cell) const {
    return api()->table_get_cell_value(m_object, cell.row(), cell.column());
  }

  u16 get_row_count() const { return api()->table_get_row_cnt(m_object); }

  u16 get_column_count() const { return api()->table_get_col_cnt(m_object); }

  lv_coord_t get_column_width(u16 column) const {
    return api()->table_get_col_width(m_object, column);
  }

  Cell get_selected_cell() const {
    u16 row = 0;
    u16 col = 0;
    api()->table_get_selected_cell(m_object, &row, &col);
    return Cell().set_row(row).set_column(col);
  }

};

API_OR_NAMED_FLAGS_OPERATOR(Table, Control)

} // namespace lvgl

#endif // LVGLAPI_LVGL_TABLE_HPP
