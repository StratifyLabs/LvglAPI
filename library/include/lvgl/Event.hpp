#ifndef LVGLAPI_LVGL_EVENT_HPP
#define LVGLAPI_LVGL_EVENT_HPP

#include <var/StringView.hpp>

#include "ObjectAccess.hpp"

namespace lvgl {

using LvglEvent = lv_event_t*;

class Event {
public:
  using Callback = void (*)(LvglEvent);

  explicit Event(LvglEvent event);

  template<class ParentType = Object> ParentType find_parent(const char * name){
    return target().find_parent<ParentType>(name);
  }

  template<class SiblingType = Object> SiblingType find_sibling(const char * name){
    return target().get_parent().find<SiblingType>(name);
  }

  template<class ChildType> static ChildType find(lv_event_t*e, const char * name){
    return Event(e).target().find<ChildType>(name);
  }

  API_NO_DISCARD EventCode code() const { return EventCode(m_event->code); }

  static const char *to_cstring(EventCode code);

  template <class TargetClass = Object> TargetClass target() const {
    return Object(m_event->target).get<TargetClass>();
  }

  template <class TargetClass = Object> TargetClass current_target() const {
    return Object(m_event->current_target).get<TargetClass>();
  }

  API_NO_DISCARD Event previous_event() const { return Event(m_event->prev); }

  // param and user_data
  template <typename ResultType> ResultType parameter() const {
    return reinterpret_cast<ResultType>(m_event->param);
  }

  template <typename ResultType> ResultType user_data() const {
    return reinterpret_cast<ResultType>(m_event->user_data);
  }

  static void send(Object receiver, EventCode code, void *user_data = nullptr) {
    Api::api()->event_send(
      receiver.object(), static_cast<lv_event_code_t>(code), user_data);
  }

private:
  lv_event_t *m_event = nullptr;
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_EVENT_HPP
