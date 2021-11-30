// Local
#include "LvglRenderer.hpp"

static void
flush_callback(lv_disp_drv_t *display_driver, const lv_area_t *area, lv_color_t *colors) {
  auto *renderer = reinterpret_cast<LvglRenderer *>(display_driver->user_data);
  renderer->flush(display_driver, area, colors);
  lv_disp_flush_ready(display_driver);
}

LvglRenderer::LvglRenderer(){

  resize_memory(lvgl::Size(max_width, max_height));

  lv_init();

  lv_disp_draw_buf_init(
    &m_display_buffer, m_image_data, nullptr,
    max_width * max_height);

  lv_disp_drv_init(&m_display_driver);

  m_display_driver.hor_res = max_width;
  m_display_driver.ver_res = max_height;
  m_display_driver.draw_buf = &m_display_buffer;
  m_display_driver.flush_cb = flush_callback;
  m_display_driver.user_data = this;

  m_display = lv_disp_drv_register(&m_display_driver);
}

void LvglRenderer::resize(lvgl::Size size){
  resize_memory(size);

  m_display_driver.hor_res = size.width();
  m_display_driver.ver_res = size.height();
  lv_disp_drv_update(m_display, &m_display_driver);
}

void LvglRenderer::resize_memory(lvgl::Size size){
  if( m_image_data  ){
    free(m_image_data);
  }
  if( m_display_data ){
    free(m_display_data);
  }
  const auto buffer_size = sizeof(lv_color_t) * size.width() * size.height();
  m_image_data = (lv_color_t*)malloc(buffer_size);
  m_display_data = (lv_color_t*)malloc(buffer_size);
  m_image = QImage(reinterpret_cast<uchar *>(m_image_data), size.width(), size.height(), image_format);
}


void LvglRenderer::flush(
  const lv_disp_drv_t *const driver,
  const lv_area_t *const area,
  const lv_color_t *colors) noexcept {
  const auto x1 = area->x1;
  const auto x2 = area->x2;
  const auto y1 = area->y1;
  const auto y2 = area->y2;
  const auto width = x2 - x1 + 1;

  for (auto y = y1; y <= y2; ++y) {
    //copy to image
    memcpy(m_image_data + y * driver->hor_res + x1, colors, sizeof(*colors) * width);
    colors += (width);
  }
}

QPixmap LvglRenderer::pixmap() const { return QPixmap::fromImage(m_image); }
