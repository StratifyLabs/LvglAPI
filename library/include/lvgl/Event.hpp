#ifndef LVGLAPI_LVGL_EVENT_HPP
#define LVGLAPI_LVGL_EVENT_HPP

#include "Style.hpp"

namespace lv {

class Object;
class Container;

enum class EventCode {
  all = LV_EVENT_ALL,
  pressed = LV_EVENT_PRESSED,
  pressing = LV_EVENT_PRESSING,
  press_lost = LV_EVENT_PRESS_LOST,
  short_clicked = LV_EVENT_SHORT_CLICKED,
  long_pressed = LV_EVENT_LONG_PRESSED,
  long_pressed_repeat = LV_EVENT_LONG_PRESSED_REPEAT,
  clicked = LV_EVENT_CLICKED,
  released = LV_EVENT_RELEASED,
  scroll_begin = LV_EVENT_SCROLL_BEGIN,
  scroll_end = LV_EVENT_SCROLL_END,
  scroll = LV_EVENT_SCROLL,
  gesture = LV_EVENT_GESTURE,
  key = LV_EVENT_KEY,

  focused = LV_EVENT_FOCUSED,
  defocused = LV_EVENT_DEFOCUSED,
  leave = LV_EVENT_LEAVE,
  hit_test = LV_EVENT_HIT_TEST,

  cover_check = LV_EVENT_COVER_CHECK,
  refresh_external_drawing_size = LV_EVENT_REFR_EXT_DRAW_SIZE,
  draw_main_begin = LV_EVENT_DRAW_MAIN_BEGIN,
  draw_main = LV_EVENT_DRAW_MAIN,
  draw_main_end = LV_EVENT_DRAW_MAIN_END,
  draw_post_begin = LV_EVENT_DRAW_POST_BEGIN,
  draw_post = LV_EVENT_DRAW_POST,
  draw_post_end = LV_EVENT_DRAW_POST_END,
  draw_part_begin = LV_EVENT_DRAW_PART_BEGIN,
  draw_part_end = LV_EVENT_DRAW_PART_END,

  value_changed = LV_EVENT_VALUE_CHANGED,
  insert = LV_EVENT_INSERT,
  refresh = LV_EVENT_REFRESH,
  ready = LV_EVENT_READY,
  cancel = LV_EVENT_CANCEL,

  delete_ = LV_EVENT_DELETE,
  child_changed = LV_EVENT_CHILD_CHANGED,
  size_changed = LV_EVENT_SIZE_CHANGED,
  style_changed = LV_EVENT_STYLE_CHANGED,
  layout_changed = LV_EVENT_LAYOUT_CHANGED,
  get_self_size = LV_EVENT_GET_SELF_SIZE
};

class Event {
public:
  Event(lv_event_t * event);

  EventCode code() const {
    return EventCode(m_event->code);
  }

  Container target() const;
  Container current_target() const;

  Event previous_event() const {
    return Event(m_event->prev);
  }

  //param and user_data

private:
  lv_event_t * m_event;
};

}

#endif // LVGLAPI_LVGL_EVENT_HPP
