#ifndef LVGLIMAGEPROVIDER_HPP
#define LVGLIMAGEPROVIDER_HPP

// 3rd Party
#include <QQuickImageProvider>
#include <QKeyEvent>
#include <lvgl.h>

#include <var/Queue.hpp>
#include <thread/Mutex.hpp>

#include "lvgl/Group.hpp"

class KeyPressEater : public QObject {
  Q_OBJECT


  struct Event {
    int key;
    int state;
  };

protected:
  bool eventFilter(QObject *obj, QEvent *event) override {
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
      thread::Mutex::Scope mutex_scope(mutex);
      QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
      m_event_queue.push({keyEvent->key(), event->type()});
      return true;
    } else {
      // standard event processing
      return QObject::eventFilter(obj, event);
    }
  }

private:
  var::Queue<Event> m_event_queue;
  thread::Mutex mutex;
public:
  Event get_last_key(){
    thread::Mutex::Scope mutex_scope(mutex);
    if( m_event_queue.count() > 0 ){
      auto result = m_event_queue.front();
      m_event_queue.pop();
      return result;
    }
    return Event();
  }
};

class LvglRenderer;
class LvglImageProvider final : public QQuickImageProvider {
  LvglRenderer &m_renderer;
  QObject *m_mouse_area = nullptr;
  lv_indev_drv_t m_mouse_driver = {};
  lv_indev_t *m_mouse_device = nullptr;

  lv_indev_drv_t m_keyboard_driver = {};
  lv_indev_t *m_keyboard_device = nullptr;
  lvgl::Group m_group;

public:
  LvglImageProvider(LvglRenderer &renderer);

  void setMouseArea(QObject *mouse_area);
  QPointF mousePosition() const;
  bool isMousePressed() const noexcept;

  QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);


  KeyPressEater * key_press_eater(){
    return &m_key_press_eater;
  }

  lvgl::Group get_keyboard_group(){
    return m_group;
  }

private:
  KeyPressEater m_key_press_eater;
};

#endif // LVGLIMAGEPROVIDER_HPP
