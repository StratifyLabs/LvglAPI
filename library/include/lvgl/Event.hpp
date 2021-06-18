#ifndef LVGLAPI_LVGL_EVENT_HPP
#define LVGLAPI_LVGL_EVENT_HPP

#include <var/StringView.hpp>

#include "Object.hpp"

namespace lv {


class Event {
public:
  Event(lv_event_t * event);

  EventCode code() const {
    return EventCode(m_event->code);
  }

  Object target() const;
  Object current_target() const;

  Event previous_event() const {
    return Event(m_event->prev);
  }

  //param and user_data
  template<typename ResultType> ResultType parameter() const {
    return reinterpret_cast<ResultType>(m_event->param);
  }

  bool is_target(const char * name) const {
    return var::StringView(Object(m_event->target).name()) == name;
  }

private:
  lv_event_t * m_event = nullptr;
};

}

#endif // LVGLAPI_LVGL_EVENT_HPP
