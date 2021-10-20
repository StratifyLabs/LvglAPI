#ifndef LVGLGRAPHICSVIEW_HPP
#define LVGLGRAPHICSVIEW_HPP

// 3rd Party
#include <QGraphicsView>
#include <lvgl/lvgl.h>

#include <lvgl/Group.hpp>
#include <var/Queue.hpp>

// Local
#include "LvglRenderer.hpp"

class LvglGraphicsView final : public QGraphicsView {
  LvglRenderer m_renderer;
  lv_indev_drv_t m_keyboard_driver = {};
  lv_indev_drv_t m_mouse_driver = {};
  lv_indev_drv_t m_mouse_wheel_driver = {};
  lv_indev_t *m_keyboard_device = nullptr;
  lv_indev_t *m_mouse_device = nullptr;
  lv_indev_t *m_mouse_wheel_device = nullptr;
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

  var::Queue<lvgl::WheelEvent> & wheel_event_queue(){
    return m_wheel_event_queue;
  }

  const var::Queue<lvgl::WheelEvent> & wheel_event_queue() const {
    return m_wheel_event_queue;
  }

private:
  struct KeyEvent {
    enum class State { released, pressed };
    State state = State::released;
    int key = 0;
  };

  struct ClickEvent {
    enum class State { released, pressed };
    State state = State::released;
    lvgl::Point point;
  };

  API_AB(LvglGraphicsView, shift, false);
  API_AB(LvglGraphicsView, control, false);
  API_AB(LvglGraphicsView, meta, false);
  var::Queue<KeyEvent> m_key_event_queue;
  var::Queue<lvgl::WheelEvent> m_wheel_event_queue;
  var::Queue<ClickEvent> m_click_event_queue;

  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

  static void read_keyboard(lv_indev_drv_t *device, lv_indev_data_t *data);
  static void read_mouse(lv_indev_drv_t *device, lv_indev_data_t *data);
  static void read_mouse_wheel(lv_indev_drv_t *device, lv_indev_data_t *data);

  void initialize_devices();
};

#endif // LVGLGRAPHICSVIEW_HPP
