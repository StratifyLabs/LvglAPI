#ifndef LVGLAPI_LVGL_CONTAINER_HPP
#define LVGLAPI_LVGL_CONTAINER_HPP

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

    Rectangle& set_blend_mode(BlendMode value){
      m_rectangle->blend_mode = lv_blend_mode_t(value);
      return *this;
    }

    Rectangle& set_background_color(Color value){
      m_rectangle->bg_color = value.get_color();
      return *this;
    }

    Rectangle& set_background_gradient_color(Color value){
      m_rectangle->bg_grad_color = value.get_color();
      return *this;
    }

    Rectangle& set_main_background_color_stop(u8 value){
      m_rectangle->bg_main_color_stop = value;
      return *this;
    }

    Rectangle& set_gradient_background_color_stop(u8 value){
      m_rectangle->bg_grad_color_stop = value;
      return *this;
    }

    Rectangle& set_background_opacity(u8 value){
      m_rectangle->bg_opa = value;
      return *this;
    }

  private:
    lv_draw_rect_dsc_t * m_rectangle;
  };

  bool is_rectangle_valid() const {
    return m_draw->rect_dsc;
  }

  Rectangle get_rectangle(){
    API_ASSERT(m_draw->rect_dsc != nullptr);
    return Rectangle(m_draw->rect_dsc);
  }

private:
  lv_obj_draw_part_dsc_t * m_draw;
};



} // namespace lvgl

#endif // LVGLAPI_LVGL_CONTAINER_HPP
