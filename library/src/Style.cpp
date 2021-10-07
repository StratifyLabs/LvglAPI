#include "lvgl/Style.hpp"
#include "lvgl/Font.hpp"

using namespace lvgl;

Style &Style::set_text_font(const Font &value) {
  return set_property(Property::text_font, PropertyValue(value.font()));
}

#define PROPERTY_CASE(x)                                                                 \
  case Property::x:                                                                      \
    return MCU_STRINGIFY(x)

const char *Style::to_cstring(Property property) {
  switch (property) {
    PROPERTY_CASE(invalid);
    PROPERTY_CASE(width);
    PROPERTY_CASE(minimum_width);
    PROPERTY_CASE(maximum_width);
    PROPERTY_CASE(height);
    PROPERTY_CASE(minimum_height);
    PROPERTY_CASE(maximum_height);
    PROPERTY_CASE(x);
    PROPERTY_CASE(y);
    PROPERTY_CASE(alignment);
    PROPERTY_CASE(transform_width);
    PROPERTY_CASE(transform_height);
    PROPERTY_CASE(translate_x);
    PROPERTY_CASE(translate_y);
    PROPERTY_CASE(transform_zoom);
    PROPERTY_CASE(transform_angle);
    PROPERTY_CASE(top_padding);
    PROPERTY_CASE(bottom_padding);
    PROPERTY_CASE(left_padding);
    PROPERTY_CASE(right_padding);
    PROPERTY_CASE(row_padding);
    PROPERTY_CASE(column_padding);
    PROPERTY_CASE(background_color);
    PROPERTY_CASE(background_color_filtered);
    PROPERTY_CASE(background_opacity);
    PROPERTY_CASE(background_gradient_color);
    PROPERTY_CASE(background_gradient_color_filtered);
    PROPERTY_CASE(background_gradient_direction);
    PROPERTY_CASE(background_main_stop);
    PROPERTY_CASE(background_gradient_stop);
    PROPERTY_CASE(background_image_source);
    PROPERTY_CASE(background_image_opacity);
    PROPERTY_CASE(background_image_recolor);
    PROPERTY_CASE(background_image_recolor_filtered);
    PROPERTY_CASE(background_image_recolor_opacity);
    PROPERTY_CASE(background_image_tiled);
    PROPERTY_CASE(border_color);
    PROPERTY_CASE(border_color_filtered);
    PROPERTY_CASE(border_opacity);
    PROPERTY_CASE(border_width);
    PROPERTY_CASE(border_side);
    PROPERTY_CASE(border_post);
    PROPERTY_CASE(outline_width);
    PROPERTY_CASE(outline_color);
    PROPERTY_CASE(outline_color_filtered);
    PROPERTY_CASE(outline_opacity);
    PROPERTY_CASE(outline_padding);
    PROPERTY_CASE(shadow_width);
    PROPERTY_CASE(shadow_x_offset);
    PROPERTY_CASE(shadow_y_offset);
    PROPERTY_CASE(shadow_spread);
    PROPERTY_CASE(shadow_color);
    PROPERTY_CASE(shadow_color_filtered);
    PROPERTY_CASE(shadow_opacity);
    PROPERTY_CASE(image_opacity);
    PROPERTY_CASE(image_recolor);
    PROPERTY_CASE(image_recolor_filtered);
    PROPERTY_CASE(image_recolor_opacity);
    PROPERTY_CASE(line_width);
    PROPERTY_CASE(line_dash_width);
    PROPERTY_CASE(line_dash_gap);
    PROPERTY_CASE(line_rounded);
    PROPERTY_CASE(line_color);
    PROPERTY_CASE(line_color_filtered);
    PROPERTY_CASE(line_opacity);
    PROPERTY_CASE(arc_width);
    PROPERTY_CASE(arc_rounded);
    PROPERTY_CASE(arc_color);
    PROPERTY_CASE(arc_color_filtered);
    PROPERTY_CASE(arc_opacity);
    PROPERTY_CASE(arc_image_source);
    PROPERTY_CASE(text_color);
    PROPERTY_CASE(text_color_filtered);
    PROPERTY_CASE(text_opacity);
    PROPERTY_CASE(text_font);
    PROPERTY_CASE(text_letter_spacing);
    PROPERTY_CASE(text_line_spacing);
    PROPERTY_CASE(text_decoration);
    PROPERTY_CASE(text_alignment);
    PROPERTY_CASE(radius);
    PROPERTY_CASE(clip_corner);
    PROPERTY_CASE(opacity);
    PROPERTY_CASE(color_filter_dsc);
    PROPERTY_CASE(color_filter_opacity);
    PROPERTY_CASE(animation_time);
    PROPERTY_CASE(animation_speed);
    PROPERTY_CASE(transition);
    PROPERTY_CASE(blend_mode);
    PROPERTY_CASE(layout);
    PROPERTY_CASE(base_direction);
    PROPERTY_CASE(any);
  }
  return "unknown";
}

#define PROPERTY_STRING_CASE(x) if( value_stringview == MCU_STRINGIFY(x) ){ return Property::x; }

Property Style::property_from_cstring(const char * value){
  var::StringView value_stringview = value;
  PROPERTY_STRING_CASE(width)
  PROPERTY_STRING_CASE(minimum_width)
  PROPERTY_STRING_CASE(maximum_width)
  PROPERTY_STRING_CASE(height)
  PROPERTY_STRING_CASE(minimum_height)
  PROPERTY_STRING_CASE(maximum_height)
  PROPERTY_STRING_CASE(x)
  PROPERTY_STRING_CASE(y)
  PROPERTY_STRING_CASE(alignment)
  PROPERTY_STRING_CASE(transform_width)
  PROPERTY_STRING_CASE(transform_height)
  PROPERTY_STRING_CASE(translate_x)
  PROPERTY_STRING_CASE(translate_y)
  PROPERTY_STRING_CASE(transform_zoom)
  PROPERTY_STRING_CASE(transform_angle)
  PROPERTY_STRING_CASE(top_padding)
  PROPERTY_STRING_CASE(bottom_padding)
  PROPERTY_STRING_CASE(left_padding)
  PROPERTY_STRING_CASE(right_padding)
  PROPERTY_STRING_CASE(row_padding)
  PROPERTY_STRING_CASE(column_padding)
  PROPERTY_STRING_CASE(background_color)
  PROPERTY_STRING_CASE(background_color_filtered)
  PROPERTY_STRING_CASE(background_opacity)
  PROPERTY_STRING_CASE(background_gradient_color)
  PROPERTY_STRING_CASE(background_gradient_color_filtered)
  PROPERTY_STRING_CASE(background_gradient_direction)
  PROPERTY_STRING_CASE(background_main_stop)
  PROPERTY_STRING_CASE(background_gradient_stop)
  PROPERTY_STRING_CASE(background_image_source)
  PROPERTY_STRING_CASE(background_image_opacity)
  PROPERTY_STRING_CASE(background_image_recolor)
  PROPERTY_STRING_CASE(background_image_recolor_filtered)
  PROPERTY_STRING_CASE(background_image_recolor_opacity)
  PROPERTY_STRING_CASE(background_image_tiled)
  PROPERTY_STRING_CASE(border_color)
  PROPERTY_STRING_CASE(border_color_filtered)
  PROPERTY_STRING_CASE(border_opacity)
  PROPERTY_STRING_CASE(border_width)
  PROPERTY_STRING_CASE(border_side)
  PROPERTY_STRING_CASE(border_post)
  PROPERTY_STRING_CASE(outline_width)
  PROPERTY_STRING_CASE(outline_color)
  PROPERTY_STRING_CASE(outline_color_filtered)
  PROPERTY_STRING_CASE(outline_opacity)
  PROPERTY_STRING_CASE(outline_padding)
  PROPERTY_STRING_CASE(shadow_width)
  PROPERTY_STRING_CASE(shadow_x_offset)
  PROPERTY_STRING_CASE(shadow_y_offset)
  PROPERTY_STRING_CASE(shadow_spread)
  PROPERTY_STRING_CASE(shadow_color)
  PROPERTY_STRING_CASE(shadow_color_filtered)
  PROPERTY_STRING_CASE(shadow_opacity)
  PROPERTY_STRING_CASE(image_opacity)
  PROPERTY_STRING_CASE(image_recolor)
  PROPERTY_STRING_CASE(image_recolor_filtered)
  PROPERTY_STRING_CASE(image_recolor_opacity)
  PROPERTY_STRING_CASE(line_width)
  PROPERTY_STRING_CASE(line_dash_width)
  PROPERTY_STRING_CASE(line_dash_gap)
  PROPERTY_STRING_CASE(line_rounded)
  PROPERTY_STRING_CASE(line_color)
  PROPERTY_STRING_CASE(line_color_filtered)
  PROPERTY_STRING_CASE(line_opacity)
  PROPERTY_STRING_CASE(arc_width)
  PROPERTY_STRING_CASE(arc_rounded)
  PROPERTY_STRING_CASE(arc_color)
  PROPERTY_STRING_CASE(arc_color_filtered)
  PROPERTY_STRING_CASE(arc_opacity)
  PROPERTY_STRING_CASE(arc_image_source)
  PROPERTY_STRING_CASE(text_color)
  PROPERTY_STRING_CASE(text_color_filtered)
  PROPERTY_STRING_CASE(text_opacity)
  PROPERTY_STRING_CASE(text_font)
  PROPERTY_STRING_CASE(text_letter_spacing)
  PROPERTY_STRING_CASE(text_line_spacing)
  PROPERTY_STRING_CASE(text_decoration)
  PROPERTY_STRING_CASE(text_alignment)
  PROPERTY_STRING_CASE(radius)
  PROPERTY_STRING_CASE(clip_corner)
  PROPERTY_STRING_CASE(opacity)
  PROPERTY_STRING_CASE(color_filter_dsc)
  PROPERTY_STRING_CASE(color_filter_opacity)
  PROPERTY_STRING_CASE(animation_time)
  PROPERTY_STRING_CASE(animation_speed)
  PROPERTY_STRING_CASE(transition)
  PROPERTY_STRING_CASE(blend_mode)
  PROPERTY_STRING_CASE(layout)
  PROPERTY_STRING_CASE(base_direction)
  PROPERTY_STRING_CASE(any)

  return Property::invalid;
}
