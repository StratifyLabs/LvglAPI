//
// Created by Tyler Gilbert on 10/4/22.
//

#ifndef LVGLAPI_LVGL_EVENTBUS_HPP
#define LVGLAPI_LVGL_EVENTBUS_HPP

#include "UserData.hpp"

#if LV_USE_MSG
namespace lvgl {

template <typename IdentifierType> class EventBus : public Api {
  EventBus() = default;

public:
  static void send(IdentifierType id) { api()->msg_send(uint32_t(id), nullptr); }

  class Subscription {
  public:
    using Callback = void (*)(IdentifierType id);
    Subscription() = default;
    Subscription(IdentifierType id, Callback callback)
      : m_unique_pointer(subscribe(id, callback), &deleter) {}

  private:
    static void deleter(void *context) { api()->msg_unsubscribe(context); }
    using UniquePointer = api::UniquePointer<void, decltype(&deleter)>;
    UniquePointer m_unique_pointer = UniquePointer(nullptr, nullptr);

    static void subscriber_callback(void *s, lv_msg_t *msg) {
      if (auto *callback = reinterpret_cast<Callback>(msg->user_data); callback) {
        callback(IdentifierType(msg->id));
      }
    }

    static void *subscribe(IdentifierType id, Callback callback) {
      return api()->msg_subsribe(
        uint32_t(id), subscriber_callback, reinterpret_cast<void *>(callback));
    }
  };

  template <typename UserDataType> class UserDataSubscription {
  public:
    UserDataSubscription() = default;
    UserDataSubscription(IdentifierType id, UserDataType *user_data)
      : m_unique_pointer(subscribe(id, user_data), &deleter) {}

  private:
    static void deleter(void *context) { api()->msg_unsubscribe(context); }
    using UniquePointer = api::UniquePointer<void, decltype(&deleter)>;
    UniquePointer m_unique_pointer = UniquePointer(nullptr, nullptr);

    static void subscriber_callback(void *s, lv_msg_t *msg) {
      if (auto *user_data = reinterpret_cast<UserDataType *>(msg->user_data); user_data) {
        user_data->handle_event(IdentifierType(msg->id));
      }
    }

    static void *subscribe(IdentifierType id, UserDataType *user_data) {
      return api()->msg_subsribe(uint32_t(id), subscriber_callback, user_data);
    }
  };
};

} // namespace lvgl
#endif

#endif // LVGLAPI_LVGL_EVENTBUS_HPP
