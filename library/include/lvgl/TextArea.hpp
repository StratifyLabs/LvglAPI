#ifndef LVGLAPI_LVGL_TEXTAREA_HPP
#define LVGLAPI_LVGL_TEXTAREA_HPP

#include <fs/File.hpp>
#include <var/View.hpp>

#include "Generic.hpp"
#include "Label.hpp"
#include "ObjectAccess.hpp"

namespace lvgl {


class TextArea : public ObjectAccess<TextArea> {
public:
  explicit TextArea(const char *name = "");
  explicit TextArea(lv_obj_t *obj) { m_object = obj; }

  static const lv_obj_class_t *get_class() { return api()->textarea_class; }

  TextArea &set_password_mode(bool value = true) {
    api()->textarea_set_password_mode(object(), value);
    return *this;
  }

  TextArea &set_one_line_mode(bool value = true) {
    api()->textarea_set_one_line(object(), value);
    return *this;
  }

  TextArea &add_character(u32 c) {
    api()->textarea_add_char(object(), c);
    return *this;
  }

  TextArea &add_text(const char *text) {
    api()->textarea_add_text(object(), text);
    return *this;
  }

  TextArea &delete_character() {
    api()->textarea_del_char(object());
    return *this;
  }

  TextArea &delete_forward_character() {
    api()->textarea_del_char_forward(object());
    return *this;
  }

  TextArea &set_placeholder_text(const char *value) {
    api()->textarea_set_placeholder_text(object(), value);
    return *this;
  }

  TextArea &set_cursor_position(int value) {
    api()->textarea_set_cursor_pos(object(), value);
    return *this;
  }

  TextArea &set_cursor_click_position(bool value) {
    api()->textarea_set_cursor_click_pos(object(), value);
    return *this;
  }

  TextArea &set_accepted_characters(const char *value) {
    api()->textarea_set_accepted_chars(object(), value);
    return *this;
  }

  TextArea &set_max_length(size_t value) {
    api()->textarea_set_max_length(object(), value);
    return *this;
  }

  TextArea &set_insert_replace_text(const char *value) {
    api()->textarea_set_insert_replace(object(), value);
    return *this;
  }

  TextArea &set_text_selection(bool value) {
    api()->textarea_set_text_selection(object(), value);
    return *this;
  }

  TextArea &set_password_show_time(const chrono::MicroTime duration) {
    api()->textarea_set_password_show_time(object(), duration.milliseconds());
    return *this;
  }

  TextArea &set_text_alignment(TextAlignment value) {
    api()->textarea_set_align(object(), lv_text_align_t(value));
    return *this;
  }

  TextArea &set_text(const char *value) {
    api()->textarea_set_text(object(), value);
    return *this;
  }

  TextArea &set_text_as_static(const char *value) {
    Label(reinterpret_cast<lv_textarea_t *>(object())->label).set_text_as_static(value);
    return *this;
  }

  API_NO_DISCARD const char *get_text() const { return api()->textarea_get_text(object()); }

  API_NO_DISCARD const char *get_placeholder_text() const {
    return api()->textarea_get_placeholder_text(m_object);
  }

  API_NO_DISCARD Label get_label() const { return Label(api()->textarea_get_label(m_object)); }

  API_NO_DISCARD int get_cursor_position() const { return api()->textarea_get_cursor_pos(m_object); }

  API_NO_DISCARD bool get_password_mode() const { return api()->textarea_get_password_mode(m_object); }

  API_NO_DISCARD bool get_one_line() const { return api()->textarea_get_one_line(m_object); }

  API_NO_DISCARD const char *get_accepted_characters() const {
    return api()->textarea_get_accepted_chars(m_object);
  }

  API_NO_DISCARD size_t get_max_length() const { return api()->textarea_get_max_length(m_object); }

  API_NO_DISCARD bool get_text_selection() const { return api()->textarea_get_text_selection(m_object); }

  API_NO_DISCARD chrono::MicroTime get_password_show_time() const {
    return api()->textarea_get_password_show_time(m_object) * 1_milliseconds;
  }

  TextArea &clear_selection() {
    api()->textarea_clear_selection(object());
    return *this;
  }

  TextArea &move_cursor_right() {
    api()->textarea_cursor_right(object());
    return *this;
  }

  TextArea &move_cursor_left() {
    api()->textarea_cursor_left(object());
    return *this;
  }

  TextArea &move_cursor_up() {
    api()->textarea_cursor_up(object());
    return *this;
  }

  TextArea &move_cursor_down() {
    api()->textarea_cursor_down(object());
    return *this;
  }

};


} // namespace lvgl

#endif // LVGLAPI_LVGL_TEXTAREA_HPP
