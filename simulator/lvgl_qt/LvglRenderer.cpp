// Local
#include "LvglRenderer.hpp"

static void lvglFlushCallback(lv_disp_drv_t* display_driver, const lv_area_t* area, lv_color_t* colors);
static void loadColorTable(QImage& image);

LvglRenderer::LvglRenderer()
    : m_display_frame1{}
    , m_display_frame2{}
    , current_frame_{}
    , m_display_driver{}
    , m_image(reinterpret_cast<uint8_t*>(current_frame_),
             sizeof(*current_frame_) / sizeof(**current_frame_),
             sizeof(current_frame_) / sizeof(*current_frame_),
             image_format)
{
  loadColorTable(m_image);
  lv_init();
  lv_disp_draw_buf_init(&m_display_buffer,
                   m_display_frame1,
                   m_display_frame2,
                   sizeof(m_display_frame1) / sizeof(*m_display_frame1));
  lv_disp_drv_init(&m_display_driver);
  m_display_driver.hor_res = max_width;
  m_display_driver.ver_res = max_height;
  m_display_driver.draw_buf    = &m_display_buffer;
  m_display_driver.flush_cb  = &lvglFlushCallback;
  m_display_driver.user_data = this;
  lv_disp_drv_register(&m_display_driver);
}

void LvglRenderer::flush(const lv_disp_drv_t* const, const lv_area_t* const area, const lv_color_t* colors) noexcept
{
  const auto x1    = area->x1;
  const auto x2    = area->x2;
  const auto y1    = area->y1;
  const auto y2    = area->y2;
  const auto width = x2 - x1;

  for (auto y = y1; y <= y2; ++y)
  {
    memcpy(&current_frame_[y][x1], colors, sizeof(*colors) * width);
    colors += (width + 1);
  }
}

QPixmap LvglRenderer::pixmap() const
{
  return QPixmap::fromImage(m_image);
}

static void lvglFlushCallback(lv_disp_drv_t* display_driver, const lv_area_t* area, lv_color_t* colors)
{
  auto* renderer = reinterpret_cast<LvglRenderer*>(display_driver->user_data);
  renderer->flush(display_driver, area, colors);
  lv_disp_flush_ready(display_driver);
}

static void loadColorTable(QImage& image)
{
#if (LV_COLOR_DEPTH == 8)
  static QVector<QRgb> Color_Table;
  Color_Table.reserve(256);
  for (auto i = 0; i < 256; ++i)
  {
    lv_color8_t truncated{};
    truncated.full = i;
    // Shift bitfields by remaining bits in a uint8_t to give their representation maximum impact
    Color_Table.push_back(qRgb(truncated.ch.red << 5, truncated.ch.green << 5, truncated.ch.blue << 6));
  }
  Color_Table[255] = ~0;
  image.setColorTable(Color_Table);
#elif (LV_COLOR_DEPTH == 1)
  static QVector<QRgb> Color_Table(256, 0);
  Color_Table[LV_COLOR_WHITE.full] = ~0;
  image.setColorTable(Color_Table);
#else
  static_cast<void>(image);
#endif
}
