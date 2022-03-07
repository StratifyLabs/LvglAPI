#include "lvgl/Event.hpp"
#include "lvgl/Object.hpp"


using namespace lvgl;

Event::Event(lv_event_t* event) : m_event(event){
  API_ASSERT(event != nullptr);
}

#define CODE_CASE(x) case EventCode::x: return MCU_STRINGIFY(x)

const char *  Event::to_cstring(EventCode code){
  switch(code){
    CODE_CASE(all);
    CODE_CASE(pressed);
    CODE_CASE(pressing);
    CODE_CASE(press_lost);
    CODE_CASE(short_clicked);
    CODE_CASE(long_pressed);
    CODE_CASE(long_pressed_repeat);
    CODE_CASE(clicked);
    CODE_CASE(released);
    CODE_CASE(scroll_begin);
    CODE_CASE(scroll_end);
    CODE_CASE(scroll);
    CODE_CASE(gesture);
    CODE_CASE(key);
    CODE_CASE(focused);
    CODE_CASE(defocused);
    CODE_CASE(leave);
    CODE_CASE(hit_test);
    CODE_CASE(cover_check);
    CODE_CASE(refresh_external_drawing_size);
    CODE_CASE(draw_main_begin);
    CODE_CASE(draw_main);
    CODE_CASE(draw_main_end);
    CODE_CASE(draw_post_begin);
    CODE_CASE(draw_post);
    CODE_CASE(draw_post_end);
    CODE_CASE(draw_part_begin);
    CODE_CASE(draw_part_end);
    CODE_CASE(value_changed);
    CODE_CASE(insert);
    CODE_CASE(refresh);
    CODE_CASE(ready);
    CODE_CASE(cancel);
    CODE_CASE(delete_);
    CODE_CASE(child_changed);
    CODE_CASE(size_changed);
    CODE_CASE(style_changed);
    CODE_CASE(layout_changed);
    CODE_CASE(get_self_size);
    CODE_CASE(notified);
    CODE_CASE(entered);
    CODE_CASE(exited);
#if defined __link
    CODE_CASE(drop_begin);
    CODE_CASE(drop_complete);
    CODE_CASE(drop_file);
    CODE_CASE(drop_text);
#endif
  }

  return "unknown";
}

