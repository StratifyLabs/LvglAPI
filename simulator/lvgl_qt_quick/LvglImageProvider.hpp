#ifndef LVGLIMAGEPROVIDER_HPP
#define LVGLIMAGEPROVIDER_HPP

// 3rd Party
#include <QQuickImageProvider>
#include <lvgl.h>

class LvglRenderer;
class LvglImageProvider final : public QQuickImageProvider {
  LvglRenderer&  m_renderer;
  QObject*       m_mouse_area;
  lv_indev_drv_t m_mouse_driver;
  lv_indev_t*    m_mouse_device;

public:
  LvglImageProvider(LvglRenderer& renderer);

  void        setMouseArea(QObject* mouse_area);
  QPointF     mousePosition() const;
  bool        isMousePressed() const noexcept;

  QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize);

};

#endif // LVGLIMAGEPROVIDER_HPP
