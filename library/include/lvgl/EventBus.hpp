//
// Created by Tyler Gilbert on 10/4/22.
//

#ifndef DESIGNLAB_EVENTBUS_HPP
#define DESIGNLAB_EVENTBUS_HPP

#include "UserData.hpp"

namespace lvgl {

template <typename IdentifierType> class EventBus : public Api {
public:
  static void send(IdentifierType id) { api()->msg_send(uint32_t(id), nullptr); }

  template <typename UserDataType> class Subscription {
  public:
    Subscription() = default;
    Subscription(IdentifierType id, UserDataType *user_data)
      : m_unique_pointer(subscribe(id, user_data), &deleter) {}

  private:
    static void deleter(void *context) { api()->msg_unsubscribe(context); }
    using UniquePointer = api::UniquePointer<void, decltype(&deleter)>;
    UniquePointer m_unique_pointer = UniquePointer(nullptr, nullptr);

    static void subscriber_callback(void *s, lv_msg_t *msg) {
      reinterpret_cast<UserDataType *>(msg->user_data)
        ->handle_event(IdentifierType(msg->id));
    }

    static void *
    subscribe(IdentifierType id, UserDataType *user_data) {
      return api()->msg_subsribe(uint32_t(id), subscriber_callback, user_data);
    }
  };
};

} // namespace lvgl
#endif // DESIGNLAB_EVENTBUS_HPP
