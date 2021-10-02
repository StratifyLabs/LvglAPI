// 3rd Party
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>

// Local
#include "LvglGraphicsView.hpp"

static void read_keyboard(lv_indev_drv_t *device, lv_indev_data_t *data);
static uint32_t toAscii(Qt::Key key);
static void read_mouse(lv_indev_drv_t *device, lv_indev_data_t *data);

LvglGraphicsView::LvglGraphicsView(QWidget *parent)
  : QGraphicsView(parent) {
  initialize_devices();
}

LvglGraphicsView::LvglGraphicsView(QGraphicsScene *scene, QWidget *parent)
  : QGraphicsView(scene, parent) {
  initialize_devices();
}

void LvglGraphicsView::initialize_devices(){
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
  m_key = static_cast<Qt::Key>(event->key());
  QGraphicsView::keyPressEvent(event);
}

void LvglGraphicsView::keyReleaseEvent(QKeyEvent *event) {
  m_key = {};
  QGraphicsView::keyReleaseEvent(event);
}

void LvglGraphicsView::mousePressEvent(QMouseEvent *event) {
  m_is_mouse_pressed = true;
  QGraphicsView::mousePressEvent(event);
}

void LvglGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
  m_is_mouse_pressed = false;
  QGraphicsView::mouseReleaseEvent(event);
}

static void read_keyboard(lv_indev_drv_t *device, lv_indev_data_t *data) {
  auto *view = static_cast<LvglGraphicsView *>(device->user_data);
  data->key = toAscii(view->key());
  data->state = (data->key == 0) ? LV_INDEV_STATE_REL : LV_INDEV_STATE_PR;
}

static uint32_t toAscii(Qt::Key key) {
  uint32_t ascii = 0;
  switch (key) {
  case Qt::Key_Up:
    ascii = LV_KEY_UP;
    break;
  case Qt::Key_Down:
    ascii = LV_KEY_DOWN;
    break;
  case Qt::Key_Right:
    ascii = LV_KEY_RIGHT;
    break;
  case Qt::Key_Left:
    ascii = LV_KEY_LEFT;
    break;
  case Qt::Key_Escape:
    ascii = LV_KEY_ESC;
    break;
  case Qt::Key_Delete:
    ascii = LV_KEY_DEL;
    break;
  case Qt::Key_Backspace:
    ascii = LV_KEY_BACKSPACE;
    break;
  case Qt::Key_Enter:
    ascii = LV_KEY_ENTER;
    break;
  case Qt::Key_Tab:
    ascii = LV_KEY_NEXT;
    break;
  case Qt::Key_Home:
    ascii = LV_KEY_HOME;
    break;
  case Qt::Key_End:
    ascii = (LV_KEY_END); // lack of parens breaks clang-format for some reason...
    break;
  default:
    ascii = key;
    break;
  }
  return ascii;
}

static void read_mouse(lv_indev_drv_t *device, lv_indev_data_t *data) {
  auto *view = static_cast<LvglGraphicsView *>(device->user_data);
  auto mouse_point = view->mousePosition();
  data->point.x = mouse_point.x();
  data->point.y = mouse_point.y();
  data->state = view->isMousePressed() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
}
