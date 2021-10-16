#ifndef LVGLAPI_LVGL_CHART_HPP
#define LVGLAPI_LVGL_CHART_HPP

#include <var/View.hpp>

#include "Bar.hpp"
#include "Color.hpp"
#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Chart : public ObjectAccess<Chart> {

  template <typename Type> class Feature {
  public:
    Feature() = default;
    Feature(lv_obj_t * object, Type *series) : m_chart(object), m_value(series) {}

    bool is_valid() const { return m_value; }

    const Type *value() const { return m_value; }

    Type *value() { return m_value; }

  protected:
    lv_obj_t * m_chart = nullptr;
    Type *m_value = nullptr;
  };

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

  class Cursor : public Feature<lv_chart_cursor_t> {
  public:
    Cursor() = default;
    Cursor(lv_obj_t * chart, lv_chart_cursor_t *value) : Feature(chart, value) {}

    Cursor &set_position(const Point &point) {
      API_ASSERT(is_valid());
      Point tmp(point);
      api()->chart_set_cursor_pos(m_chart, m_value, tmp.point());
      return *this;
    }

    Point get_point() const {
      API_ASSERT(is_valid());
      return Point(api()->chart_get_cursor_point(m_chart, m_value));
    }

  };

  class Series : public Feature<lv_chart_series_t> {
  public:
    Series() = default;
    Series(lv_obj_t *chart, lv_chart_series_t *series)
      : Feature(chart, series) {}

    var::View get_x_values() const {
      API_ASSERT(is_valid());
      return var::View(
        Chart::api()->chart_get_x_array(m_chart, m_value),
        get_point_count() * sizeof(lv_coord_t));
    }

    var::View get_y_values() const {
      API_ASSERT(is_valid());
      return var::View(
        Chart::api()->chart_get_y_array(m_chart, m_value),
        get_point_count() * sizeof(lv_coord_t));
    }

    u16 get_point_count() const {
      API_ASSERT(is_valid());
      return Chart::api()->chart_get_point_count(m_chart);
    }

    Series &set_external_x_values(var::View values) {
      API_ASSERT(values.count<lv_coord_t>() >= get_point_count() * sizeof(lv_coord_t));
      Chart::api()->chart_set_ext_x_array(m_chart, m_value, values.to<lv_coord_t>());
      return *this;
    }

    Series &set_external_y_values(var::View values) {
      API_ASSERT(values.count<lv_coord_t>() >= get_point_count() * sizeof(lv_coord_t));
      Chart::api()->chart_set_ext_y_array(m_chart, m_value, values.to<lv_coord_t>());
      return *this;
    }

    u16 get_x_start_point() const {
      return api()->chart_get_x_start_point(m_chart, m_value);
    }

    Point get_point_by_id(u16 id) {
      Point result;
      api()->chart_get_point_pos_by_id(m_chart, m_value, id, result.point());
      return result;
    }

    Series &remove_series() {
      API_ASSERT(is_valid());
      api()->chart_remove_series(m_chart, m_value);
      return *this;
    }

    Series &hide_series() {
      API_ASSERT(is_valid());
      api()->chart_hide_series(m_chart, m_value, true);
      return *this;
    }

    Series &show_series() {
      API_ASSERT(is_valid());
      api()->chart_hide_series(m_chart, m_value, false);
      return *this;
    }

    Series &set_series_color(Color color) {
      API_ASSERT(is_valid());
      api()->chart_set_series_color(m_chart, m_value, color.get_color());
      return *this;
    }

    Series &set_x_start_point(u16 id) {
      API_ASSERT(is_valid());
      api()->chart_set_x_start_point(m_chart, m_value, id);
      return *this;
    }

    Series get_next_series() const {
      API_ASSERT(is_valid());
      return Series(m_chart, api()->chart_get_series_next(m_chart, m_value));
    }

    Series &set_cursor_point(Cursor cursor, u16 id) {
      API_ASSERT(cursor.is_valid());
      api()->chart_set_cursor_point(m_chart, cursor.value(), m_value, id);
      return *this;
    }

    Series &set_all_values(lv_coord_t value) {
      api()->chart_set_all_value(m_chart, m_value, value);
      return *this;
    }

    Series &set_next_value(lv_coord_t value) {
      api()->chart_set_next_value(m_chart, m_value, value);
      return *this;
    }

    Series &set_next_value(const Point &value) {
      api()->chart_set_next_value2(m_chart, m_value, value.x(), value.y());
      return *this;
    }

    Series &set_value_by_id(u16 id, lv_coord_t value) {
      api()->chart_set_value_by_id(m_chart, m_value, id, value);
      return *this;
    }

    Series &set_value_by_id(u16 id, const Point &value) {
      api()->chart_set_value_by_id2(m_chart, m_value, id, value.x(), value.y());
      return *this;
    }

  };

  explicit Chart(const char *name);

  static const lv_obj_class_t * get_class(){
    return api()->chart_class;
  }

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
    API_AF(Tick, lv_coord_t, draw_size, 20);
  };

  Chart &set_tick(Axis axis, const Tick &tick) {
    api()->chart_set_axis_tick(
      object(), static_cast<lv_chart_axis_t>(axis), tick.major_length(),
      tick.minor_length(), tick.major_count(), tick.minor_count(),
      tick.is_labels_enabled(), tick.draw_size());
    return *this;
  }

  Type get_type() const { return Type(api()->chart_get_type(object())); }

  u16 get_point_count() const { return api()->chart_get_point_count(object()); }

  Chart &refresh() {
    api()->chart_refresh(object());
    return *this;
  }

  Series add_series(Color color, Axis axis) {
    return Series(
      object(), api()->chart_add_series(
                  object(), color.get_color(), static_cast<lv_chart_axis_t>(axis)));
  }

  u32 get_pressed_point() const { return api()->chart_get_pressed_point(object()); }

  Chart &add_cursor(Color color, Direction direction) {
    api()->chart_add_cursor(
      object(), color.get_color(), static_cast<lv_dir_t>(direction));
    return *this;
  }


private:
  OBJECT_ACCESS_FRIENDS();
  explicit Chart(lv_obj_t *object) { m_object = object; }
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_CHART_HPP
