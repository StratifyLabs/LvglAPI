// Local
#include "LvglRenderer.hpp"

static void flush_callback(
  lv_disp_drv_t *display_driver,
  const lv_area_t *area,
  lv_color_t *colors) {
  auto *renderer = reinterpret_cast<LvglRenderer *>(display_driver->user_data);
  renderer->flush(display_driver, area, colors);
  lv_disp_flush_ready(display_driver);
}

LvglRenderer::LvglRenderer()
  : m_image(
    reinterpret_cast<uint8_t *>(m_current_frame),
    sizeof(*m_current_frame) / sizeof(**m_current_frame),
    sizeof(m_current_frame) / sizeof(*m_current_frame),
    image_format) {

  lv_init();

  lv_disp_draw_buf_init(
    &m_display_buffer, m_display_frame1, m_display_frame2,
    sizeof(m_display_frame1) / sizeof(*m_display_frame1));

  lv_disp_drv_init(&m_display_driver);

  m_display_driver.hor_res = max_width;
  m_display_driver.ver_res = max_height;
  m_display_driver.draw_buf = &m_display_buffer;
  m_display_driver.flush_cb = flush_callback;
  m_display_driver.user_data = this;

  lv_disp_drv_register(&m_display_driver);
}

void LvglRenderer::flush(
  const lv_disp_drv_t *const,
  const lv_area_t *const area,
  const lv_color_t *colors) noexcept {
  const auto x1 = area->x1;
  const auto x2 = area->x2;
  const auto y1 = area->y1;
  const auto y2 = area->y2;
  const auto width = x2 - x1 + 1;

  printf("flush\n");
  for (auto y = y1; y <= y2; ++y) {
    memcpy(&m_current_frame[y][x1], colors, sizeof(*colors) * width);
    colors += (width);
  }
}

QPixmap LvglRenderer::pixmap() const { return QPixmap::fromImage(m_image); }


