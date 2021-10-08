#include "lvgl/Style.hpp"
#include "lvgl/Font.hpp"

using namespace lvgl;

Style &Style::set_text_font(const Font &value) {
  return set_property(Property::text_font, PropertyValue(value.font()));
}

#define PROPERTY_CASE(x, y)                                                              \
  case x::y:                                                                             \
    return MCU_STRINGIFY(y)

const char *Style::to_cstring(Property property) {
  switch (property) {
    PROPERTY_CASE(Property, invalid);
    PROPERTY_CASE(Property, width);
    PROPERTY_CASE(Property, minimum_width);
    PROPERTY_CASE(Property, maximum_width);
    PROPERTY_CASE(Property, height);
    PROPERTY_CASE(Property, minimum_height);
    PROPERTY_CASE(Property, maximum_height);
    PROPERTY_CASE(Property, x);
    PROPERTY_CASE(Property, y);
    PROPERTY_CASE(Property, alignment);
    PROPERTY_CASE(Property, transform_width);
    PROPERTY_CASE(Property, transform_height);
    PROPERTY_CASE(Property, translate_x);
    PROPERTY_CASE(Property, translate_y);
    PROPERTY_CASE(Property, transform_zoom);
    PROPERTY_CASE(Property, transform_angle);
    PROPERTY_CASE(Property, top_padding);
    PROPERTY_CASE(Property, bottom_padding);
    PROPERTY_CASE(Property, left_padding);
    PROPERTY_CASE(Property, right_padding);
    PROPERTY_CASE(Property, row_padding);
    PROPERTY_CASE(Property, column_padding);
    PROPERTY_CASE(Property, background_color);
    PROPERTY_CASE(Property, background_color_filtered);
    PROPERTY_CASE(Property, background_opacity);
    PROPERTY_CASE(Property, background_gradient_color);
    PROPERTY_CASE(Property, background_gradient_color_filtered);
    PROPERTY_CASE(Property, background_gradient_direction);
    PROPERTY_CASE(Property, background_main_stop);
    PROPERTY_CASE(Property, background_gradient_stop);
    PROPERTY_CASE(Property, background_image_source);
    PROPERTY_CASE(Property, background_image_opacity);
    PROPERTY_CASE(Property, background_image_recolor);
    PROPERTY_CASE(Property, background_image_recolor_filtered);
    PROPERTY_CASE(Property, background_image_recolor_opacity);
    PROPERTY_CASE(Property, background_image_tiled);
    PROPERTY_CASE(Property, border_color);
    PROPERTY_CASE(Property, border_color_filtered);
    PROPERTY_CASE(Property, border_opacity);
    PROPERTY_CASE(Property, border_width);
    PROPERTY_CASE(Property, border_side);
    PROPERTY_CASE(Property, border_post);
    PROPERTY_CASE(Property, outline_width);
    PROPERTY_CASE(Property, outline_color);
    PROPERTY_CASE(Property, outline_color_filtered);
    PROPERTY_CASE(Property, outline_opacity);
    PROPERTY_CASE(Property, outline_padding);
    PROPERTY_CASE(Property, shadow_width);
    PROPERTY_CASE(Property, shadow_x_offset);
    PROPERTY_CASE(Property, shadow_y_offset);
    PROPERTY_CASE(Property, shadow_spread);
    PROPERTY_CASE(Property, shadow_color);
    PROPERTY_CASE(Property, shadow_color_filtered);
    PROPERTY_CASE(Property, shadow_opacity);
    PROPERTY_CASE(Property, image_opacity);
    PROPERTY_CASE(Property, image_recolor);
    PROPERTY_CASE(Property, image_recolor_filtered);
    PROPERTY_CASE(Property, image_recolor_opacity);
    PROPERTY_CASE(Property, line_width);
    PROPERTY_CASE(Property, line_dash_width);
    PROPERTY_CASE(Property, line_dash_gap);
    PROPERTY_CASE(Property, line_rounded);
    PROPERTY_CASE(Property, line_color);
    PROPERTY_CASE(Property, line_color_filtered);
    PROPERTY_CASE(Property, line_opacity);
    PROPERTY_CASE(Property, arc_width);
    PROPERTY_CASE(Property, arc_rounded);
    PROPERTY_CASE(Property, arc_color);
    PROPERTY_CASE(Property, arc_color_filtered);
    PROPERTY_CASE(Property, arc_opacity);
    PROPERTY_CASE(Property, arc_image_source);
    PROPERTY_CASE(Property, text_color);
    PROPERTY_CASE(Property, text_color_filtered);
    PROPERTY_CASE(Property, text_opacity);
    PROPERTY_CASE(Property, text_font);
    PROPERTY_CASE(Property, text_letter_spacing);
    PROPERTY_CASE(Property, text_line_spacing);
    PROPERTY_CASE(Property, text_decoration);
    PROPERTY_CASE(Property, text_alignment);
    PROPERTY_CASE(Property, radius);
    PROPERTY_CASE(Property, clip_corner);
    PROPERTY_CASE(Property, opacity);
    PROPERTY_CASE(Property, color_filter_descriptor);
    PROPERTY_CASE(Property, color_filter_opacity);
    PROPERTY_CASE(Property, animation_time);
    PROPERTY_CASE(Property, animation_speed);
    PROPERTY_CASE(Property, transition);
    PROPERTY_CASE(Property, blend_mode);
    PROPERTY_CASE(Property, layout);
    PROPERTY_CASE(Property, base_direction);
    PROPERTY_CASE(Property, any);
  }
  return "unknown";
}

#define PROPERTY_STRING_CASE(x, y)                                                       \
  if (value_stringview == MCU_STRINGIFY(x)) {                                            \
    return x::y;                                                                         \
  }

Property Style::property_from_cstring(const char *value) {
  const var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(Property, width)
  PROPERTY_STRING_CASE(Property, minimum_width)
  PROPERTY_STRING_CASE(Property, maximum_width)
  PROPERTY_STRING_CASE(Property, height)
  PROPERTY_STRING_CASE(Property, minimum_height)
  PROPERTY_STRING_CASE(Property, maximum_height)
  PROPERTY_STRING_CASE(Property, x)
  PROPERTY_STRING_CASE(Property, y)
  PROPERTY_STRING_CASE(Property, alignment)
  PROPERTY_STRING_CASE(Property, transform_width)
  PROPERTY_STRING_CASE(Property, transform_height)
  PROPERTY_STRING_CASE(Property, translate_x)
  PROPERTY_STRING_CASE(Property, translate_y)
  PROPERTY_STRING_CASE(Property, transform_zoom)
  PROPERTY_STRING_CASE(Property, transform_angle)
  PROPERTY_STRING_CASE(Property, top_padding)
  PROPERTY_STRING_CASE(Property, bottom_padding)
  PROPERTY_STRING_CASE(Property, left_padding)
  PROPERTY_STRING_CASE(Property, right_padding)
  PROPERTY_STRING_CASE(Property, row_padding)
  PROPERTY_STRING_CASE(Property, column_padding)
  PROPERTY_STRING_CASE(Property, background_color)
  PROPERTY_STRING_CASE(Property, background_color_filtered)
  PROPERTY_STRING_CASE(Property, background_opacity)
  PROPERTY_STRING_CASE(Property, background_gradient_color)
  PROPERTY_STRING_CASE(Property, background_gradient_color_filtered)
  PROPERTY_STRING_CASE(Property, background_gradient_direction)
  PROPERTY_STRING_CASE(Property, background_main_stop)
  PROPERTY_STRING_CASE(Property, background_gradient_stop)
  PROPERTY_STRING_CASE(Property, background_image_source)
  PROPERTY_STRING_CASE(Property, background_image_opacity)
  PROPERTY_STRING_CASE(Property, background_image_recolor)
  PROPERTY_STRING_CASE(Property, background_image_recolor_filtered)
  PROPERTY_STRING_CASE(Property, background_image_recolor_opacity)
  PROPERTY_STRING_CASE(Property, background_image_tiled)
  PROPERTY_STRING_CASE(Property, border_color)
  PROPERTY_STRING_CASE(Property, border_color_filtered)
  PROPERTY_STRING_CASE(Property, border_opacity)
  PROPERTY_STRING_CASE(Property, border_width)
  PROPERTY_STRING_CASE(Property, border_side)
  PROPERTY_STRING_CASE(Property, border_post)
  PROPERTY_STRING_CASE(Property, outline_width)
  PROPERTY_STRING_CASE(Property, outline_color)
  PROPERTY_STRING_CASE(Property, outline_color_filtered)
  PROPERTY_STRING_CASE(Property, outline_opacity)
  PROPERTY_STRING_CASE(Property, outline_padding)
  PROPERTY_STRING_CASE(Property, shadow_width)
  PROPERTY_STRING_CASE(Property, shadow_x_offset)
  PROPERTY_STRING_CASE(Property, shadow_y_offset)
  PROPERTY_STRING_CASE(Property, shadow_spread)
  PROPERTY_STRING_CASE(Property, shadow_color)
  PROPERTY_STRING_CASE(Property, shadow_color_filtered)
  PROPERTY_STRING_CASE(Property, shadow_opacity)
  PROPERTY_STRING_CASE(Property, image_opacity)
  PROPERTY_STRING_CASE(Property, image_recolor)
  PROPERTY_STRING_CASE(Property, image_recolor_filtered)
  PROPERTY_STRING_CASE(Property, image_recolor_opacity)
  PROPERTY_STRING_CASE(Property, line_width)
  PROPERTY_STRING_CASE(Property, line_dash_width)
  PROPERTY_STRING_CASE(Property, line_dash_gap)
  PROPERTY_STRING_CASE(Property, line_rounded)
  PROPERTY_STRING_CASE(Property, line_color)
  PROPERTY_STRING_CASE(Property, line_color_filtered)
  PROPERTY_STRING_CASE(Property, line_opacity)
  PROPERTY_STRING_CASE(Property, arc_width)
  PROPERTY_STRING_CASE(Property, arc_rounded)
  PROPERTY_STRING_CASE(Property, arc_color)
  PROPERTY_STRING_CASE(Property, arc_color_filtered)
  PROPERTY_STRING_CASE(Property, arc_opacity)
  PROPERTY_STRING_CASE(Property, arc_image_source)
  PROPERTY_STRING_CASE(Property, text_color)
  PROPERTY_STRING_CASE(Property, text_color_filtered)
  PROPERTY_STRING_CASE(Property, text_opacity)
  PROPERTY_STRING_CASE(Property, text_font)
  PROPERTY_STRING_CASE(Property, text_letter_spacing)
  PROPERTY_STRING_CASE(Property, text_line_spacing)
  PROPERTY_STRING_CASE(Property, text_decoration)
  PROPERTY_STRING_CASE(Property, text_alignment)
  PROPERTY_STRING_CASE(Property, radius)
  PROPERTY_STRING_CASE(Property, clip_corner)
  PROPERTY_STRING_CASE(Property, opacity)
  PROPERTY_STRING_CASE(Property, color_filter_descriptor)
  PROPERTY_STRING_CASE(Property, color_filter_opacity)
  PROPERTY_STRING_CASE(Property, animation_time)
  PROPERTY_STRING_CASE(Property, animation_speed)
  PROPERTY_STRING_CASE(Property, transition)
  PROPERTY_STRING_CASE(Property, blend_mode)
  PROPERTY_STRING_CASE(Property, layout)
  PROPERTY_STRING_CASE(Property, base_direction)
  PROPERTY_STRING_CASE(Property, any)

  return Property::invalid;
}

const char *Style::to_cstring(TextDecoration value) {
  switch (value) {
    PROPERTY_CASE(TextDecoration, none);
    PROPERTY_CASE(TextDecoration, underline);
    PROPERTY_CASE(TextDecoration, strikethrough);
  }
  return "unknown";
}
TextDecoration text_decoration_from_cstring(const char *value) {
  const var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(TextDecoration, underline)
  PROPERTY_STRING_CASE(TextDecoration, strikethrough)
  return TextDecoration::none;
}

const char *Style::to_cstring(TextAlignment value) {
  switch (value) {
    PROPERTY_CASE(TextAlignment, auto_);
    PROPERTY_CASE(TextAlignment, left);
    PROPERTY_CASE(TextAlignment, right);
    PROPERTY_CASE(TextAlignment, center);
  }
  return "unknown";
}
TextAlignment Style::text_alignment_from_cstring(const char *value) {
  const var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(TextAlignment, left);
  PROPERTY_STRING_CASE(TextAlignment, right);
  PROPERTY_STRING_CASE(TextAlignment, center);
  return TextAlignment::auto_;
}

const char *Style::to_cstring(BorderSide value) {
  switch (value) {
    PROPERTY_CASE(BorderSide, none);
    PROPERTY_CASE(BorderSide, bottom);
    PROPERTY_CASE(BorderSide, top);
    PROPERTY_CASE(BorderSide, left);
    PROPERTY_CASE(BorderSide, right);
    PROPERTY_CASE(BorderSide, full);
    PROPERTY_CASE(BorderSide, internal);
  }
  return "unknown";
}
BorderSide Style::border_side_from_cstring(const char *value) {
  const var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(BorderSide, bottom);
  PROPERTY_STRING_CASE(BorderSide, top);
  PROPERTY_STRING_CASE(BorderSide, left);
  PROPERTY_STRING_CASE(BorderSide, right);
  PROPERTY_STRING_CASE(BorderSide, full);
  PROPERTY_STRING_CASE(BorderSide, internal);
  return BorderSide::none;
}

const char *Style::to_cstring(GradientDirection value) {
  switch (value) {
    PROPERTY_CASE(GradientDirection, none);
    PROPERTY_CASE(GradientDirection, horizontal);
    PROPERTY_CASE(GradientDirection, vertical);
  }
  return "unknown";
}
GradientDirection Style::gradient_direction_from_cstring(const char *value) {
  const var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(GradientDirection, horizontal);
  PROPERTY_STRING_CASE(GradientDirection, vertical);
  return GradientDirection::none;
}

const char *Style::to_cstring(BaseDirection value) {
  switch (value) {
    PROPERTY_CASE(BaseDirection, auto_);
    PROPERTY_CASE(BaseDirection, left_to_right);
    PROPERTY_CASE(BaseDirection, right_to_left);
    PROPERTY_CASE(BaseDirection, neutral);
    PROPERTY_CASE(BaseDirection, weak);
  }
  return "unknown";
}
BaseDirection Style::base_direction_from_cstring(const char *value) {
  const var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(BaseDirection, left_to_right);
  PROPERTY_STRING_CASE(BaseDirection, right_to_left);
  PROPERTY_STRING_CASE(BaseDirection, neutral);
  PROPERTY_STRING_CASE(BaseDirection, weak);
  return BaseDirection::auto_;
}

const char *Style::to_cstring(Direction value) {
  switch (value) {
    PROPERTY_CASE(Direction, none);
    PROPERTY_CASE(Direction, left);
    PROPERTY_CASE(Direction, right);
    PROPERTY_CASE(Direction, top);
    PROPERTY_CASE(Direction, bottom);
    PROPERTY_CASE(Direction, horizontal);
    PROPERTY_CASE(Direction, vertical);
    PROPERTY_CASE(Direction, all);
  }
  return "unknown";
}
Direction Style::direction_from_cstring(const char *value) {
  const var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(Direction, none);
  PROPERTY_STRING_CASE(Direction, left);
  PROPERTY_STRING_CASE(Direction, right);
  PROPERTY_STRING_CASE(Direction, top);
  PROPERTY_STRING_CASE(Direction, bottom);
  PROPERTY_STRING_CASE(Direction, horizontal);
  PROPERTY_STRING_CASE(Direction, vertical);
  PROPERTY_STRING_CASE(Direction, all);
  return Direction::none;
}

const char *Style::to_cstring(Alignment value) {
  switch (value) {
    PROPERTY_CASE(Alignment, default_);
    PROPERTY_CASE(Alignment, top_left);
    PROPERTY_CASE(Alignment, top_middle);
    PROPERTY_CASE(Alignment, top_right);
    PROPERTY_CASE(Alignment, bottom_left);
    PROPERTY_CASE(Alignment, bottom_middle);
    PROPERTY_CASE(Alignment, bottom_right);
    PROPERTY_CASE(Alignment, left_middle);
    PROPERTY_CASE(Alignment, right_middle);
    PROPERTY_CASE(Alignment, center);
    PROPERTY_CASE(Alignment, out_top_left);
    PROPERTY_CASE(Alignment, out_top_middle);
    PROPERTY_CASE(Alignment, out_top_right);
    PROPERTY_CASE(Alignment, out_bottom_left);
    PROPERTY_CASE(Alignment, out_bottom_middle);
    PROPERTY_CASE(Alignment, out_bottom_right);
    PROPERTY_CASE(Alignment, out_left_top);
    PROPERTY_CASE(Alignment, out_left_middle);
    PROPERTY_CASE(Alignment, out_left_bottom);
    PROPERTY_CASE(Alignment, out_right_top);
    PROPERTY_CASE(Alignment, out_right_middle);
    PROPERTY_CASE(Alignment, out_right_bottom);
  }
  return "unknown";
}
Alignment Style::alignment_from_cstring(const char *value) {
  const var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(Alignment, top_left);
  PROPERTY_STRING_CASE(Alignment, top_middle);
  PROPERTY_STRING_CASE(Alignment, top_right);
  PROPERTY_STRING_CASE(Alignment, bottom_left);
  PROPERTY_STRING_CASE(Alignment, bottom_middle);
  PROPERTY_STRING_CASE(Alignment, bottom_right);
  PROPERTY_STRING_CASE(Alignment, left_middle);
  PROPERTY_STRING_CASE(Alignment, right_middle);
  PROPERTY_STRING_CASE(Alignment, center);
  PROPERTY_STRING_CASE(Alignment, out_top_left);
  PROPERTY_STRING_CASE(Alignment, out_top_middle);
  PROPERTY_STRING_CASE(Alignment, out_top_right);
  PROPERTY_STRING_CASE(Alignment, out_bottom_left);
  PROPERTY_STRING_CASE(Alignment, out_bottom_middle);
  PROPERTY_STRING_CASE(Alignment, out_bottom_right);
  PROPERTY_STRING_CASE(Alignment, out_left_top);
  PROPERTY_STRING_CASE(Alignment, out_left_middle);
  PROPERTY_STRING_CASE(Alignment, out_left_bottom);
  PROPERTY_STRING_CASE(Alignment, out_right_top);
  PROPERTY_STRING_CASE(Alignment, out_right_middle);
  PROPERTY_STRING_CASE(Alignment, out_right_bottom);
  return Alignment::default_;
}

const char *Style::to_cstring(FlexFlow value) {
  switch (value) {
    PROPERTY_CASE(FlexFlow, row);
    PROPERTY_CASE(FlexFlow, column);
    PROPERTY_CASE(FlexFlow, row_wrap);
    PROPERTY_CASE(FlexFlow, row_reverse);
    PROPERTY_CASE(FlexFlow, row_wrap_reverse);
    PROPERTY_CASE(FlexFlow, column_wrap);
    PROPERTY_CASE(FlexFlow, column_reverse);
    PROPERTY_CASE(FlexFlow, column_wrap_reverse);
  }
  return "unknown";
}
FlexFlow Style::flex_flow_from_cstring(const char *value) {
  const var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(FlexFlow, column);
  PROPERTY_STRING_CASE(FlexFlow, row_wrap);
  PROPERTY_STRING_CASE(FlexFlow, row_reverse);
  PROPERTY_STRING_CASE(FlexFlow, row_wrap_reverse);
  PROPERTY_STRING_CASE(FlexFlow, column_wrap);
  PROPERTY_STRING_CASE(FlexFlow, column_reverse);
  PROPERTY_STRING_CASE(FlexFlow, column_wrap_reverse);
  return FlexFlow::row;
}

const char *Style::to_cstring(FlexAlign value) {
  switch (value) {
    PROPERTY_CASE(FlexAlign, start);
    PROPERTY_CASE(FlexAlign, end);
    PROPERTY_CASE(FlexAlign, center);
    PROPERTY_CASE(FlexAlign, space_evenly);
    PROPERTY_CASE(FlexAlign, space_around);
    PROPERTY_CASE(FlexAlign, space_between);
  }
  return "unknown";
}
FlexAlign Style::flex_align_from_cstring(const char *value) {
  const var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(FlexAlign, start);
  PROPERTY_STRING_CASE(FlexAlign, end);
  PROPERTY_STRING_CASE(FlexAlign, center);
  PROPERTY_STRING_CASE(FlexAlign, space_evenly);
  PROPERTY_STRING_CASE(FlexAlign, space_around);
  PROPERTY_STRING_CASE(FlexAlign, space_between);
  return FlexAlign::start;
}

const char *Style::to_cstring(State value) {
  switch (value) {
    PROPERTY_CASE(State, default_);
    PROPERTY_CASE(State, checked);
    PROPERTY_CASE(State, focused);
    PROPERTY_CASE(State, focus_key);
    PROPERTY_CASE(State, edited);
    PROPERTY_CASE(State, hovered);
    PROPERTY_CASE(State, pressed);
    PROPERTY_CASE(State, scrolled);
    PROPERTY_CASE(State, disabled);
    PROPERTY_CASE(State, user1);
    PROPERTY_CASE(State, user2);
    PROPERTY_CASE(State, user3);
    PROPERTY_CASE(State, user4);
    PROPERTY_CASE(State, any);
  }
  return "unknown";
}
State Style::state_from_cstring(const char *value) {
  const var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(State, checked);
  PROPERTY_STRING_CASE(State, focused);
  PROPERTY_STRING_CASE(State, focus_key);
  PROPERTY_STRING_CASE(State, edited);
  PROPERTY_STRING_CASE(State, hovered);
  PROPERTY_STRING_CASE(State, pressed);
  PROPERTY_STRING_CASE(State, scrolled);
  PROPERTY_STRING_CASE(State, disabled);
  PROPERTY_STRING_CASE(State, user1);
  PROPERTY_STRING_CASE(State, user2);
  PROPERTY_STRING_CASE(State, user3);
  PROPERTY_STRING_CASE(State, user4);
  PROPERTY_STRING_CASE(State, any);
  return State::default_;
}

const char *Style::to_cstring(ScrollBarMode value) {
  switch (value) {
    PROPERTY_CASE(ScrollBarMode, off);
    PROPERTY_CASE(ScrollBarMode, on);
    PROPERTY_CASE(ScrollBarMode, active);
    PROPERTY_CASE(ScrollBarMode, auto_);
  }
  return "unknown";
}
ScrollBarMode Style::scroll_bar_mode_from_cstring(const char *value) {
  const var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(ScrollBarMode, on);
  PROPERTY_STRING_CASE(ScrollBarMode, active);
  PROPERTY_STRING_CASE(ScrollBarMode, auto_);
  return ScrollBarMode::off;
}

const char *Style::to_cstring(ScrollSnap value) {
  switch (value) {
    PROPERTY_CASE(ScrollSnap, off);
    PROPERTY_CASE(ScrollSnap, start);
    PROPERTY_CASE(ScrollSnap, end);
    PROPERTY_CASE(ScrollSnap, center);
  }
  return "unknown";
}
ScrollSnap Style::scroll_snap_mode_from_cstring(const char *value) {
  const var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(ScrollSnap, start);
  PROPERTY_STRING_CASE(ScrollSnap, end);
  PROPERTY_STRING_CASE(ScrollSnap, center);
  return ScrollSnap::off;
}

const char *Style::to_cstring(IsAnimate value) {
  switch (value) {
    PROPERTY_CASE(IsAnimate, no);
    PROPERTY_CASE(IsAnimate, yes);
    PROPERTY_CASE(IsAnimate, repeat_infinite);
  }
  return "unknown";
}
IsAnimate Style::is_animate_mode_from_cstring(const char *value) {
  const var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(IsAnimate, yes);
  PROPERTY_STRING_CASE(IsAnimate, repeat_infinite);
  return IsAnimate::no;
}

const char *Style::to_cstring(Part value) {
  switch (value) {
    PROPERTY_CASE(Part, main);
    PROPERTY_CASE(Part, scrollbar);
    PROPERTY_CASE(Part, indicator);
    PROPERTY_CASE(Part, knob);
    PROPERTY_CASE(Part, selected);
    PROPERTY_CASE(Part, items);
    PROPERTY_CASE(Part, ticks);
    PROPERTY_CASE(Part, cursor);
    PROPERTY_CASE(Part, any);
  }
  return "unknown";
}
Part Style::part_mode_from_cstring(const char *value) {
  const var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(Part, scrollbar);
  PROPERTY_STRING_CASE(Part, indicator);
  PROPERTY_STRING_CASE(Part, knob);
  PROPERTY_STRING_CASE(Part, selected);
  PROPERTY_STRING_CASE(Part, items);
  PROPERTY_STRING_CASE(Part, ticks);
  PROPERTY_STRING_CASE(Part, cursor);
  PROPERTY_STRING_CASE(Part, any);
  return Part::main;
}

const char *Style::to_cstring(BlendMode value) {
  switch (value) {
    PROPERTY_CASE(BlendMode, normal);
    PROPERTY_CASE(BlendMode, additive);
    PROPERTY_CASE(BlendMode, subtractive);
  }
  return "unknown";
}
BlendMode Style::blend_mode_from_cstring(const char *value) {
  const var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(BlendMode, additive);
  PROPERTY_STRING_CASE(BlendMode, subtractive);
  return BlendMode::normal;
}
