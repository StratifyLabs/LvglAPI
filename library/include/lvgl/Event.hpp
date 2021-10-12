#ifndef LVGLAPI_LVGL_EVENT_HPP
#define LVGLAPI_LVGL_EVENT_HPP

#include <var/StringView.hpp>

#include "ObjectAccess.hpp"

namespace lvgl {

class Event {
public:
  using Callback = void (*)(lv_event_t *);

  Event(lv_event_t *event);

  EventCode code() const { return EventCode(m_event->code); }

  static const char *to_cstring(EventCode code);

  template <class TargetClass = Object> TargetClass target() const {
    return Object(m_event->target).get<TargetClass>();
  }

  template <class TargetClass = Object> TargetClass current_target() const {
    return Object(m_event->current_target).get<TargetClass>();
  }

  Event previous_event() const { return Event(m_event->prev); }

  // param and user_data
  template <typename ResultType> ResultType parameter() const {
    return reinterpret_cast<ResultType>(m_event->param);
  }

  template <typename ResultType> ResultType user_data() const {
    return reinterpret_cast<ResultType>(m_event->user_data);
  }

  static void send(Object receiver, EventCode code, void *context = nullptr) {
    Api::api()->event_send(
      receiver.object(), static_cast<lv_event_code_t>(code), context);
  }

private:
  lv_event_t *m_event = nullptr;
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_EVENT_HPP
