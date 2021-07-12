#ifndef LVGLAPI_LVGL_CHART_HPP
#define LVGLAPI_LVGL_CHART_HPP

#include "Bar.hpp"
#include "Color.hpp"
#include "ObjectAccess.hpp"

namespace lvgl {

class Chart : public ObjectAccess<Chart> {
public:
  enum class Type {
    none = LV_CHART_TYPE_NONE,
    line = LV_CHART_TYPE_LINE,
    bar = LV_CHART_TYPE_BAR,
    scatter = LV_CHART_TYPE_SCATTER
  };

  enum class UpdateMode {
    shift = LV_CHART_UPDATE_MODE_SHIFT,
    circular = LV_CHART_UPDATE_MODE_CIRCULAR
  };

  enum class Axis {
    primary_y = LV_CHART_AXIS_PRIMARY_Y,
    secondary_y = LV_CHART_AXIS_SECONDARY_Y,
    primary_x = LV_CHART_AXIS_PRIMARY_X,
    secondary_x = LV_CHART_AXIS_SECONDARY_X
  };

  class Series {
  public:

    Series(lv_chart_series_t * series) : m_series(series) {}

    const lv_chart_series_t * series() const {
      return m_series;
    }

    lv_chart_series_t * series() {
      return m_series;
    }
  private:
    lv_chart_series_t * m_series;
  };

  class Create : public CreateAccess<Create> {
  public:
    Create(const char *name) : CreateAccess(name) {}
  };

  Chart(Object parent, const Create &options);

  Chart &set_type(Type value) {
    api()->chart_set_type(object(), static_cast<lv_chart_type_t>(value));
    return *this;
  }

  Chart &set_point_count(u16 value) {
    api()->chart_set_point_count(object(), value);
    return *this;
  }

  Chart &set_range(Axis axis, Range range) {
    api()->chart_set_range(
      object(), static_cast<lv_chart_axis_t>(axis), range.minimum(), range.maximum());
    return *this;
  }

  Chart &set_update_mode(UpdateMode value) {
    api()->chart_set_update_mode(object(), static_cast<lv_chart_update_mode_t>(value));
    return *this;
  }

  Chart &set_divider_line_count(u16 horizontal, u16 vertical) {
    api()->chart_set_div_line_count(object(), horizontal, vertical);
    return *this;
  }

  Chart &set_zoom_x(u16 value) {
    api()->chart_set_zoom_x(object(), value);
    return *this;
  }

  Chart &set_zoom_y(u16 value) {
    api()->chart_set_zoom_y(object(), value);
    return *this;
  }

  u16 get_zoom_x() const { return api()->chart_get_zoom_x(object()); }

  u16 get_zoom_y() const { return api()->chart_get_zoom_y(object()); }

  class Tick {
    API_AF(Tick, lv_coord_t, major_length, 10);
    API_AF(Tick, lv_coord_t, minor_length, 5);
    API_AF(Tick, lv_coord_t, major_count, 5);
    API_AF(Tick, lv_coord_t, minor_count, 10);
    API_AB(Tick, labels_enabled, true);
    API_AF(Tick, lv_coord_t, draw_size, 10);
  };

  Chart &set_tick(Axis axis, const Tick &tick) {
    api()->chart_set_axis_tick(
      object(), static_cast<lv_chart_axis_t>(axis), tick.major_length(),
      tick.minor_length(), tick.major_count(), tick.minor_count(),
      tick.is_labels_enabled(), tick.draw_size());
    return *this;
  }

  Type get_type() const {
    return Type(api()->chart_get_type(object()));
  }

  u16 get_point_count() const {
    return api()->chart_get_point_count(object());
  }

  u16 get_x_start_point(Series series) const {
    return api()->chart_get_x_start_point(object(), series.series());
  }

  Point get_point_by_id(Series series, u16 id){
    Point result;
    api()->chart_get_point_pos_by_id(object(), series.series(), id, result.point());
    return result;
  }

  Chart & refresh(){
    api()->chart_refresh(object());
    return *this;
  }

  Series add_series(Color color, Axis axis){
    return Series(api()->chart_add_series(object(), color.get_color(), static_cast<lv_chart_axis_t>(axis)));
  }

  Chart & remove_series(Series series){
    api()->chart_remove_series(object(), series.series());
    return *this;
  }

  Chart & hide_series(Series series){
    api()->chart_hide_series(object(), series.series(), true);
    return *this;
  }

  Chart & show_series(Series series){
    api()->chart_hide_series(object(), series.series(), false);
    return *this;
  }

  Chart& set_series_color(Series series, Color color){
    api()->chart_set_series_color(object(), series.series(), color.get_color());
    return *this;
  }

  Chart & set_x_start_point(Series series, u16 id){
    api()->chart_set_x_start_point(object(), series.series(), id);
    return *this;
  }

  Series get_next_series(Series series) const {
    return Series(api()->chart_get_series_next(object(), series.series()));
  }

  Chart & add_cursor(Color color, Direction direction){
    api()->chart_add_cursor(object(), color.get_color(), static_cast<lv_dir_t>(direction));
    return *this;
  }

  Chart & set_cursor_position(lv_chart_cursor_t * cursor, const Point & point){
    Point tmp(point);
    api()->chart_set_cursor_pos(object(), cursor, tmp.point());
    return *this;
  }

  Chart & set_cursor_point(lv_chart_cursor_t * cursor, Series series, u16 id){
    api()->chart_set_cursor_point(object(), cursor, series.series(), id);
    return *this;
  }

  Point get_cursor_point(lv_chart_cursor_t * cursor) const {
    return Point(api()->chart_get_cursor_point(m_object, cursor));
  }

  Chart & set_all_value(Series series, lv_coord_t value){
    api()->chart_set_all_value(object(), series.series(), value);
    return *this;
  }

  Chart & set_next_value(Series series, lv_coord_t value){
    api()->chart_set_next_value(object(), series.series(), value);
    return *this;
  }

  Chart & set_next_value(Series series, const Point & value){
    api()->chart_set_next_value2(object(), series.series(), value.x(), value.y());
    return *this;
  }

  Chart & set_value_by_id(Series series, u16 id, lv_coord_t value){
    api()->chart_set_value_by_id(object(), series.series(), id, value);
    return *this;
  }

  Chart & set_value_by_id(Series series, u16 id, const Point & value){
    api()->chart_set_value_by_id2(object(), series.series(), id, value.x(), value.y());
    return *this;
  }

  Chart & set_external_y_array(Series series, lv_coord_t array[]){
    api()->chart_set_ext_y_array(object(), series.series(), array);
    return *this;
  }

  Chart & set_external_x_array(Series series, lv_coord_t array[]){
    api()->chart_set_ext_x_array(object(), series.series(), array);
    return *this;
  }

  u32 get_pressed_point() const {
    return api()->chart_get_pressed_point(object());
  }


};

} // namespace lvgl

#endif // LVGLAPI_LVGL_CHART_HPP
