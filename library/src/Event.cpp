#include "lvgl/Event.hpp"
#include "lvgl/Object.hpp"


using namespace lv;

Event::Event(lv_event_t* event) : m_event(event){}


Object Event::target() const {
  return Object(m_event->target);
}

Object Event::current_target() const {
  return Object(m_event->current_target);
}
