#ifndef LVGLGRAPHICSVIEW_HPP
#define LVGLGRAPHICSVIEW_HPP

// 3rd Party
#include <QGraphicsView>
#include <lvgl/lvgl.h>

#include <lvgl/Group.hpp>

// Local
#include "LvglRenderer.hpp"

class LvglRenderer;
class LvglGraphicsView final : public QGraphicsView {
  LvglRenderer m_renderer;
  lv_indev_drv_t m_keyboard_driver = {};
  lv_indev_drv_t m_mouse_driver = {};
  lv_indev_t *m_keyboard_device = nullptr;
  lv_indev_t *m_mouse_device = nullptr;
  Qt::Key m_key;
  bool m_is_mouse_pressed = false;

public:
  LvglGraphicsView(QWidget *parent = nullptr);
  LvglGraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);

  void tick();
  lv_indev_t *keyboard_device() { return m_keyboard_device; }
  Qt::Key key() const noexcept;
  QPointF mousePosition() const;
  bool isMousePressed() const noexcept;

private:
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

  void initialize_devices();
};

#endif // LVGLGRAPHICSVIEW_HPP
