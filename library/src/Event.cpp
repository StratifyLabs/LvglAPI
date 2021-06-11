#include "lvgl/Event.hpp"
#include "lvgl/Object.hpp"


using namespace lv;

Event::Event(lv_event_t* event) : m_event(event){}


Container Event::target() const {
  return Container(m_event->target);
}

Container Event::current_target() const {
  return Container(m_event->current_target);
}
