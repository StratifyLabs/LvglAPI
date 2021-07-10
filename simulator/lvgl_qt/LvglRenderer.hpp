#ifndef LVGLRENDERER_HPP
#define LVGLRENDERER_HPP

// Standard
#include <cstddef>
#include <cstdint>

// 3rd Party
#include <QImage>
#include <QPixmap>

#include "lvgl.h"

#if (LV_COLOR_DEPTH == 32)
#define LVGL_SIM_QT_LVGL_RENDERER_IMAGE_FORMAT (QImage::Format_ARGB32)
#elif ((LV_COLOR_DEPTH == 16) && (LV_COLOR_16_SWAP == 0))
#define LVGL_SIM_QT_LVGL_RENDERER_IMAGE_FORMAT (QImage::Format_RGB16)
#else
#define LVGL_SIM_QT_LVGL_RENDERER_IMAGE_FORMAT (QImage::Format_Indexed8)
#endif

class LvglRenderer {
public:
  static constexpr QImage::Format image_format =
      LVGL_SIM_QT_LVGL_RENDERER_IMAGE_FORMAT;
  static constexpr int tick_perios_ms = 16;
  static constexpr int max_height = 240;
  static constexpr int max_width = 320;

private:
  lv_color_t m_display_frame1[max_width * max_height];
  lv_color_t m_display_frame2[max_width * max_height];
  lv_color_t current_frame_[max_height][max_width];
  lv_disp_draw_buf_t m_display_buffer;
  lv_disp_drv_t m_display_driver;
  QImage m_image;

public:
  LvglRenderer();
  void flush(const lv_disp_drv_t *display_driver, const lv_area_t *area,
             const lv_color_t *colors) noexcept;
  QPixmap pixmap() const;
};

#endif // LVGLRENDERER_HPP
