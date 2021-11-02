#ifndef LVGLAPI_LVGL_METER_HPP
#define LVGLAPI_LVGL_METER_HPP

#include "Color.hpp"
#include "ObjectAccess.hpp"

namespace lvgl {

class Meter : public ObjectAccess<Meter> {
public:
  class Scale {
  public:
    explicit Scale(lv_meter_scale_t *scale) : m_scale(scale) {}

    API_NO_DISCARD const lv_meter_scale_t *scale() const { return m_scale; }

    lv_meter_scale_t *scale() { return m_scale; }

  private:
    lv_meter_scale_t *m_scale = nullptr;
  };

  class Indicator {
  public:
    explicit Indicator(lv_meter_indicator_t *indicator) : m_indicator(indicator) {}

    API_NO_DISCARD const lv_meter_indicator_t *indicator() const { return m_indicator; }

    auto *indicator() { return m_indicator; }

  private:
    lv_meter_indicator_t *m_indicator = nullptr;
  };

  explicit Meter(const char *name = "");
  explicit Meter(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->meter_class; }

  Scale add_scale() { return Scale(api()->meter_add_scale(object())); }

  class Tick {
    API_AF(Tick, u16, count, 0);
    API_AF(Tick, u16, skip_minor_count, 0);
    API_AF(Tick, u16, length, 0);
    API_AF(Tick, u16, width, 0);
    API_AF(Tick, u16, label_gap, 0);
    API_AC(Tick, Color, color);
  };

  Meter &set_scale_ticks(Scale scale, const Tick &tick) {
    api()->meter_set_scale_ticks(
      object(), scale.scale(), tick.count(), tick.width(), tick.length(),
      tick.color().get_color());
    return *this;
  }

  Meter &set_scale_major_ticks(Scale scale, const Tick &tick) {
    api()->meter_set_scale_major_ticks(
      object(), scale.scale(), tick.skip_minor_count(), tick.width(), tick.length(),
      tick.color().get_color(), tick.label_gap());
    return *this;
  }

  class ScaleRange {
    API_AF(ScaleRange, u32, angle_range, 270);
    API_AF(ScaleRange, u32, rotation, 90);
    API_AF(ScaleRange, u32, minimum, 0);
    API_AF(ScaleRange, u32, maximum, 100);
  };

  Meter &set_scale_range(Scale scale, const ScaleRange &range) {
    api()->meter_set_scale_range(
      object(), scale.scale(), range.minimum(), range.maximum(), range.angle_range(),
      range.rotation());
    return *this;
  }

  Indicator add_needle_line(Scale scale, u16 width, Color color, s16 r_mod) {
    return Indicator(api()->meter_add_needle_line(
      object(), scale.scale(), width, color.get_color(), r_mod));
  }

  Indicator add_needle_image(Scale scale, const void *src, const Point &pivot) {
    return Indicator(
      api()->meter_add_needle_img(object(), scale.scale(), src, pivot.x(), pivot.y()));
  }

  Indicator add_arc(Scale scale, u16 width, Color color, s16 r_mod) {
    return Indicator(
      api()->meter_add_arc(object(), scale.scale(), width, color.get_color(), r_mod));
  }

  Indicator add_local_scale_lines(Scale scale, Color start, Color end, s16 width_mod) {
    return Indicator(api()->meter_add_scale_lines(
      object(), scale.scale(), start.get_color(), end.get_color(), true, width_mod));
  }

  Indicator add_scale_lines(Scale scale, Color start, Color end, s16 width_mod) {
    return Indicator(api()->meter_add_scale_lines(
      object(), scale.scale(), start.get_color(), end.get_color(), false, width_mod));
  }

  Meter &set_indicator_value(Indicator indicator, s32 value) {
    api()->meter_set_indicator_value(object(), indicator.indicator(), value);
    return *this;
  }

  Meter &set_indicator_start_value(Indicator indicator, s32 value) {
    api()->meter_set_indicator_start_value(object(), indicator.indicator(), value);
    return *this;
  }

  Meter &set_indicator_end_value(Indicator indicator, s32 value) {
    api()->meter_set_indicator_start_value(object(), indicator.indicator(), value);
    return *this;
  }
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_METER_HPP
