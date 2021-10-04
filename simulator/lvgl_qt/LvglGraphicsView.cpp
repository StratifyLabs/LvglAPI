// 3rd Party
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>

// Local
#include "LvglGraphicsView.hpp"

LvglGraphicsView::LvglGraphicsView(QWidget *parent) : QGraphicsView(parent) {
  initialize_devices();
}

LvglGraphicsView::LvglGraphicsView(QGraphicsScene *scene, QWidget *parent)
  : QGraphicsView(scene, parent) {
  initialize_devices();
}

void LvglGraphicsView::initialize_devices() {
  lv_indev_drv_init(&m_keyboard_driver);
  m_keyboard_driver.type = LV_INDEV_TYPE_KEYPAD;
  m_keyboard_driver.user_data = this;
  m_keyboard_driver.read_cb = read_keyboard;
  m_keyboard_device = lv_indev_drv_register(&m_keyboard_driver);

  lv_indev_drv_init(&m_mouse_driver);
  m_mouse_driver.type = LV_INDEV_TYPE_POINTER;
  m_mouse_driver.user_data = this;
  m_mouse_driver.read_cb = read_mouse;
  m_mouse_device = lv_indev_drv_register(&m_mouse_driver);
}

void LvglGraphicsView::tick() {
  lv_tick_inc(LvglRenderer::tick_perios_ms);
  lv_task_handler();

  QGraphicsScene *scene = this->scene();
  scene->clear();

  const auto *item = scene->addPixmap(m_renderer.pixmap());
  fitInView(item);
}

Qt::Key LvglGraphicsView::key() const noexcept { return m_key; }

QPointF LvglGraphicsView::mousePosition() const {
  return mapToScene(mapFromGlobal(QCursor::pos()));
}

bool LvglGraphicsView::isMousePressed() const noexcept { return m_is_mouse_pressed; }

void LvglGraphicsView::keyPressEvent(QKeyEvent *event) {
  key_event_queue.push({KeyEvent::State::pressed, event->key()});
}

void LvglGraphicsView::keyReleaseEvent(QKeyEvent *event) {
  key_event_queue.push({KeyEvent::State::released, event->key()});
}

void LvglGraphicsView::mousePressEvent(QMouseEvent *event) {
  m_is_mouse_pressed = true;
  QGraphicsView::mousePressEvent(event);
}

void LvglGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
  m_is_mouse_pressed = false;
  QGraphicsView::mouseReleaseEvent(event);
}

void LvglGraphicsView::read_keyboard(lv_indev_drv_t *device, lv_indev_data_t *data) {
  auto *view = reinterpret_cast<LvglGraphicsView *>(device->user_data);

  auto &keys = view->key_event_queue;

  if (keys.count()) {
    const auto &event = keys.front();
    data->state = event.state == KeyEvent::State::pressed ? LV_INDEV_STATE_PRESSED
                                                          : LV_INDEV_STATE_RELEASED;

    if (event.state == KeyEvent::State::pressed) {
      if (event.key == Qt::Key_Shift) {
        view->set_shift();
      } else if (event.key == Qt::Key_Control) {
        view->set_control();
      } else if (event.key == Qt::Key_Meta) {
        view->set_meta();
      }
    } else {
      if (event.key == Qt::Key_Shift) {
        view->set_shift(false);
      } else if (event.key == Qt::Key_Control) {
        view->set_control(false);
      } else if (event.key == Qt::Key_Meta) {
        view->set_meta(false);
      }
    }

    data->key = [&](int key) -> int {
      if (key == Qt::Key_PageUp) {
        return LV_KEY_NEXT;
      }
      if (key == Qt::Key_PageDown) {
        return LV_KEY_PREV;
      }
      if (key == Qt::Key_Return) {
        return LV_KEY_ENTER;
      }
      if (key == Qt::Key_Enter) {
        return LV_KEY_ENTER;
      }
      if (key == Qt::Key_Up) {
        return LV_KEY_UP;
      }
      if (key == Qt::Key_Down) {
        return LV_KEY_DOWN;
      }
      if (key == Qt::Key_Right) {
        return LV_KEY_RIGHT;
      }
      if (key == Qt::Key_Left) {
        return LV_KEY_LEFT;
      }
      if (key == Qt::Key_Direction_R) {
        return LV_KEY_RIGHT;
      }
      if (key == Qt::Key_Direction_L) {
        return LV_KEY_LEFT;
      }
      if (key == Qt::Key_Escape) {
        return LV_KEY_ESC;
      }
      if (key == Qt::Key_Delete) {
        return LV_KEY_DEL;
      }
      if (key == Qt::Key_Backspace) {
        return LV_KEY_BACKSPACE;
      }
      if (key == Qt::Key_Home) {
        return LV_KEY_HOME;
      }
      if (key == Qt::Key_End) {
        return LV_KEY_END;
      }
      if ((key == Qt::Key_Shift) || (key == Qt::Key_Control) || (key == Qt::Key_Meta)) {
        return 0;
      }

      if ((view->is_shift() == false) && key >= 'A' && key <= 'Z') {
        key = key - 'A' + 'a';
      }
      return key;
    }(event.key);

    data->continue_reading = true;
    keys.pop();
  } else {
    data->continue_reading = false;
  }
}

void LvglGraphicsView::read_mouse(lv_indev_drv_t *device, lv_indev_data_t *data) {
  auto *view = static_cast<LvglGraphicsView *>(device->user_data);
  auto mouse_point = view->mousePosition();
  data->point.x = mouse_point.x();
  data->point.y = mouse_point.y();
  data->state = view->isMousePressed() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
}
