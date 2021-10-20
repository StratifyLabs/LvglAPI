// 3rd Party
#include <QApplication>
#include <QClipboard>
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

#if 0
  lv_indev_drv_init(&m_mouse_wheel_driver);
  m_mouse_wheel_driver.type = LV_INDEV_TYPE_ENCODER;
  m_mouse_wheel_driver.user_data = this;
  m_mouse_wheel_driver.read_cb = read_mouse_wheel;
  m_mouse_wheel_device = lv_indev_drv_register(&m_mouse_wheel_driver);
#endif
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
  m_key_event_queue.push({KeyEvent::State::pressed, event->key()});
}

void LvglGraphicsView::keyReleaseEvent(QKeyEvent *event) {
  m_key_event_queue.push({KeyEvent::State::released, event->key()});
}

void LvglGraphicsView::mousePressEvent(QMouseEvent *event) {
  QGraphicsView::mousePressEvent(event);
  m_is_mouse_pressed = true;
  const auto position = mousePosition();
  m_click_event_queue.push(
    {ClickEvent::State::pressed, lvgl::Point(position.x(), position.y())});
}

void LvglGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
  QGraphicsView::mouseReleaseEvent(event);
  m_is_mouse_pressed = false;
  const auto position = mousePosition();
  m_click_event_queue.push(
    {ClickEvent::State::released, lvgl::Point(position.x(), position.y())});
}

void LvglGraphicsView::wheelEvent(QWheelEvent *event) {
  const auto pixel_count = event->pixelDelta();
  const auto degree_count = event->angleDelta();

  auto get_mouse_point = [&]() {
    const auto position = mousePosition();
    return lvgl::Point(position.x(), position.y());
  };

  if (!pixel_count.isNull()) {
    m_wheel_event_queue.push(
      {lvgl::WheelEvent::Type::pixel, lvgl::Point(pixel_count.x(), pixel_count.y()),
       get_mouse_point()});
  } else if (!degree_count.isNull()) {
    m_wheel_event_queue.push(
      {lvgl::WheelEvent::Type::degree, lvgl::Point(degree_count.x(), degree_count.y()),
       get_mouse_point()});
  }

  event->accept();
}

void LvglGraphicsView::read_keyboard(lv_indev_drv_t *device, lv_indev_data_t *data) {
  auto *view = reinterpret_cast<LvglGraphicsView *>(device->user_data);

  auto &keys = view->m_key_event_queue;

  *data = lv_indev_data_t{};

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

    data->key = [&](int key, KeyEvent::IsClipboard is_clipboard) -> int {

      if (key == Qt::Key_PageUp) {
        return LV_KEY_NEXT;
      }
      if (key == Qt::Key_Tab) {
        if (view->is_shift()) {
          return LV_KEY_PREV;
        }
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
        if( view->is_control() ){
          return LV_KEY_END;
        }
        return LV_KEY_RIGHT;
      }
      if (key == Qt::Key_Left) {
        if( view->is_control() ){
          return LV_KEY_HOME;
        }
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

      if (
        (key == Qt::Key_V) && view->is_control()
        && (event.state == KeyEvent::State::pressed)) {
        const auto text = QApplication::clipboard()->text();
        keys.push({KeyEvent::State::pressed, 0, KeyEvent::IsClipboard::yes})
          .push({KeyEvent::State::released, 0, KeyEvent::IsClipboard::yes});
        for (const auto value : text) {
          keys
            .push({KeyEvent::State::pressed, value.unicode(), KeyEvent::IsClipboard::yes})
            .push(
              {KeyEvent::State::released, value.unicode(), KeyEvent::IsClipboard::yes});
        }
        return 0;
      }

      if (
        (is_clipboard == KeyEvent::IsClipboard::no) && (view->is_shift() == false)
        && (key >= 'A') && (key <= 'Z')) {
        key = key - 'A' + 'a';
      }
      return key;
    }(event.key, event.is_clipboard);

    keys.pop();
  }
  data->continue_reading = data->key && keys.count() > 0;
}

void LvglGraphicsView::read_mouse(lv_indev_drv_t *device, lv_indev_data_t *data) {
  auto *view = static_cast<LvglGraphicsView *>(device->user_data);

  auto &events = view->m_click_event_queue;

  if (events.count()) {
    const auto &event = events.front();
    data->point.x = event.point.x();
    data->point.y = event.point.y();
    data->state = (event.state == ClickEvent::State::pressed) ? LV_INDEV_STATE_PRESSED
                                                              : LV_INDEV_STATE_RELEASED;
    events.pop();
  } else {
    auto mouse_point = view->mousePosition();
    data->point.x = mouse_point.x();
    data->point.y = mouse_point.y();
    data->state =
      view->isMousePressed() ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
  }
  data->continue_reading = 0;
}

void LvglGraphicsView::read_mouse_wheel(lv_indev_drv_t *, lv_indev_data_t *) {
  // currently mouse wheel is used to emulate an encoder (left, right arrows)
  // it needs to be used for scrolling to work well here

#if 0
  auto *view = static_cast<LvglGraphicsView *>(device->user_data);
  auto mouse_point = view->mousePosition();
  data->point.x = mouse_point.x();
  data->point.y = mouse_point.y();
  data->state = view->isMousePressed() ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
#endif
}
