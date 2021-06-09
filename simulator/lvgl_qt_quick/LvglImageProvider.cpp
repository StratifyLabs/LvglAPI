// 3rd Party
#include <QObject>

// Local
#include "LvglImageProvider.hpp"
#include "LvglRenderer.hpp"

static void mouseRead(lv_indev_drv_t *device, lv_indev_data_t *data);

LvglImageProvider::LvglImageProvider(LvglRenderer &renderer)
    : QQuickImageProvider(QQuickImageProvider::Pixmap), m_renderer{renderer},
      m_mouse_area{nullptr}, m_mouse_driver{}, m_mouse_device{nullptr} {
  lv_indev_drv_init(&m_mouse_driver);
  m_mouse_driver.type = LV_INDEV_TYPE_POINTER;
  m_mouse_driver.user_data = this;
  m_mouse_driver.read_cb = mouseRead;
  m_mouse_device = lv_indev_drv_register(&m_mouse_driver);
}

QPixmap LvglImageProvider::requestPixmap(const QString &, QSize *size,
                                         const QSize &requestedSize) {
  if (size != nullptr) {
    *size = {LvglRenderer::max_width, LvglRenderer::max_height};
  }

  lv_tick_inc(LvglRenderer::tick_perios_ms);
  lv_task_handler();

  return m_renderer.pixmap().scaled(
      requestedSize.width() > 0 ? requestedSize.width()
                                : LvglRenderer::max_width,
      requestedSize.height() > 0 ? requestedSize.height()
                                 : LvglRenderer::max_height);
}

void LvglImageProvider::setMouseArea(QObject *mouse_area) {
  m_mouse_area = mouse_area;
}

QPointF LvglImageProvider::mousePosition() const {
  QPointF position{};
  if (m_mouse_area != nullptr) {
    auto xScale =
        LvglRenderer::max_width / m_mouse_area->property("width").toFloat();
    auto yScale =
        LvglRenderer::max_height / m_mouse_area->property("height").toFloat();
    position.setX(m_mouse_area->property("mouseX").toFloat() * xScale);
    position.setY(m_mouse_area->property("mouseY").toFloat() * yScale);
  }
  return position;
}

bool LvglImageProvider::isMousePressed() const noexcept {
  bool is_pressed = false;
  if (m_mouse_area != nullptr) {
    is_pressed = m_mouse_area->property("pressedButtons").toInt() != 0;
  }
  return is_pressed;
}

static void mouseRead(lv_indev_drv_t *device, lv_indev_data_t *data) {
  auto *view = static_cast<LvglImageProvider *>(device->user_data);
  auto mouse_point = view->mousePosition();
  data->point.x = mouse_point.x();
  data->point.y = mouse_point.y();
  data->state = view->isMousePressed() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
}
