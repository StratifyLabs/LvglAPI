#ifndef LVGLAPI_LVGL_DWAW_HPP
#define LVGLAPI_LVGL_DWAW_HPP

#include "Types.hpp"
#include "Color.hpp"

namespace lvgl {


class Draw {
public:
  Draw(lv_obj_draw_part_dsc_t * value) : m_draw(value){}

  class Rectangle {
  public:
    Rectangle(lv_draw_rect_dsc_t * value) : m_rectangle(value){}

    Rectangle& set_radius(lv_coord_t value){
      m_rectangle->radius = value;
      return *this;
    }

    auto radius() const {
      return m_rectangle->radius;
    }

    Rectangle& set_blend_mode(BlendMode value){
      m_rectangle->blend_mode = lv_blend_mode_t(value);
      return *this;
    }

    auto blend_mode() const {
      return BlendMode(m_rectangle->blend_mode);
    }

    Rectangle& set_background_color(Color value){
      m_rectangle->bg_color = value.get_color();
      return *this;
    }

    auto background_color() const {
      return Color(m_rectangle->bg_color);
    }

    Rectangle& set_background_gradient_color(Color value){
      m_rectangle->bg_grad_color = value.get_color();
      return *this;
    }

    auto background_gradient_color() const {
      return Color(m_rectangle->bg_grad_color);
    }

    Rectangle& set_main_background_color_stop(u8 value){
      m_rectangle->bg_main_color_stop = value;
      return *this;
    }

    Rectangle& set_gradient_background_color_stop(u8 value){
      m_rectangle->bg_grad_color_stop = value;
      return *this;
    }

    Rectangle& set_background_opacity(Opacity value){
      m_rectangle->bg_opa = lv_opa_t(value);
      return *this;
    }

    Rectangle& set_background_gradient_direction(GradientDirection value){
      m_rectangle->bg_opa = lv_grad_dir_t(value);
      return *this;
    }

    Rectangle& set_background_image_source(const void * value){
      m_rectangle->bg_img_src = value;
      return *this;
    }

    Rectangle& set_background_image_symbol_font(const void * value){
      m_rectangle->bg_img_symbol_font = value;
      return *this;
    }

    Rectangle& set_background_image_recolor(Color value){
      m_rectangle->bg_img_recolor = value.get_color();
      return *this;
    }

    Rectangle& set_background_image_opacity(Opacity value){
      m_rectangle->bg_img_opa = lv_opa_t(value);
      return *this;
    }

    Rectangle& set_background_image_recolor_opacity(Opacity value){
      m_rectangle->bg_img_recolor_opa = lv_opa_t(value);
      return *this;
    }

    Rectangle& set_border_color(Color value){
      m_rectangle->border_color = value.get_color();
      return *this;
    }

    Rectangle& set_border_width(lv_coord_t value){
      m_rectangle->border_width = value;
      return *this;
    }

    Rectangle& set_border_opacity(Opacity value){
      m_rectangle->border_opa = lv_opa_t(value);
      return *this;
    }

    Rectangle& set_border_side(BorderSide value){
      m_rectangle->border_side = lv_border_side_t(value);
      return *this;
    }

    Rectangle& set_outline_color(Color value){
      m_rectangle->outline_color = value.get_color();
      return *this;
    }

    Rectangle& set_outline_width(lv_coord_t value){
      m_rectangle->outline_width = value;
      return *this;
    }

    Rectangle& set_outline_opacity(Opacity value){
      m_rectangle->outline_opa = lv_opa_t(value);
      return *this;
    }

    Rectangle& set_outline_padding(lv_coord_t value){
      m_rectangle->outline_opa = lv_border_side_t(value);
      return *this;
    }

    Rectangle& set_shadow_color(Color value){
      m_rectangle->shadow_color = value.get_color();
      return *this;
    }

    Rectangle& set_shadow_width(lv_coord_t value){
      m_rectangle->shadow_width = value;
      return *this;
    }

    Rectangle& set_shadow_x_offset(lv_coord_t value){
      m_rectangle->shadow_ofs_x = value;
      return *this;
    }

    Rectangle& set_shadow_y_offset(lv_coord_t value){
      m_rectangle->shadow_ofs_y = value;
      return *this;
    }

    Rectangle& set_shadow_spread(lv_coord_t value){
      m_rectangle->shadow_spread = value;
      return *this;
    }

    Rectangle& set_shadow_opacity(Opacity value){
      m_rectangle->shadow_opa = lv_opa_t(value);
      return *this;
    }


  private:
    lv_draw_rect_dsc_t * m_rectangle;
  };

  bool is_rectangle_valid() const {
    return m_draw->rect_dsc;
  }

  auto get_rectangle(){
    API_ASSERT(m_draw->rect_dsc != nullptr);
    return Rectangle(m_draw->rect_dsc);
  }

  auto id() const {
    return m_draw->id;
  }

  Part part() const {
    return Part(m_draw->part);
  }

  auto radius() const {
    return m_draw->radius;
  }

  auto value() const {
    return m_draw->value;
  }

private:
  lv_obj_draw_part_dsc_t * m_draw;
};



} // namespace lvgl

#endif // LVGLAPI_LVGL_DWAW_HPP
