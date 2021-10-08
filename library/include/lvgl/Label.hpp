#ifndef LVGLAPI_LVGL_LABEL_HPP
#define LVGLAPI_LVGL_LABEL_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Label : public ObjectAccess<Label> {
public:

  enum class LongMode {
    wrap = LV_LABEL_LONG_WRAP,
    dot = LV_LABEL_LONG_DOT,
    scroll = LV_LABEL_LONG_SCROLL,
    scroll_circular = LV_LABEL_LONG_SCROLL_CIRCULAR,
    clip = LV_LABEL_LONG_CLIP
  };

  explicit Label(const char * name) : ObjectAccess(name){}
  explicit Label(const Context & context) : ObjectAccess(context.cast_as_name()){}

  static const lv_obj_class_t * get_class(){
    return api()->label_class;
  }

  static void configure_name_as_text(Label & label){
    label.set_text(label.name());
  }

  static void configure_name_as_text_centered(Label & label){
    configure_name_as_text(label);
    label.set_text_alignment(TextAlignment::center);
  }

  Label & set_text(const char * value){
    api()->label_set_text(m_object, value);
    return *this;
  }

  Label & set_text_static(const char * value){
    api()->label_set_text_static(m_object, value);
    return *this;
  }

  Label & set_long_mode(LongMode value){
    api()->label_set_long_mode(m_object, static_cast<lv_label_long_mode_t>(value));
    return *this;
  }

  Label & set_recolor(bool value = true){
    api()->label_set_recolor(m_object, value);
    return *this;
  }

  Label & set_text_select_start(size_t value){
    api()->label_set_text_sel_start(m_object, value);
    return *this;
  }

  Label & set_text_select_end(size_t value){
    api()->label_set_text_sel_end(m_object, value);
    return *this;
  }

  char * get_text() const {
    return api()->label_get_text(m_object);
  }

  LongMode get_long_mode() const {
    return LongMode(api()->label_get_long_mode(m_object));
  }

  bool is_recolor() const {
    return api()->label_get_recolor(m_object);
  }

  Point get_letter_position(u32 value)const{
    Point position;
    api()->label_get_letter_pos(m_object, value, position.point());
    return position;
  }

  u32 get_letter_on(const Point & position)const{
    Point tmp(position);
    return api()->label_get_letter_on(m_object, tmp.point());
  }

  bool is_character_under_position(Point & position)const{
    Point tmp(position);
    return api()->label_is_char_under_pos(m_object, tmp.point());
  }

  u32 get_text_selection_start() const {
    return api()->label_get_text_selection_start(m_object);
  }

  u32 get_text_selection_end() const {
    return api()->label_get_text_selection_end(m_object);
  }

  Label & insert_text(u32 position, const char * text){
    api()->label_ins_text(m_object, position, text);
    return *this;
  }

  Label & cut_text(u32 position, u32 count){
    api()->label_cut_text(m_object, position, count);
    return *this;
  }

private:
  OBJECT_ACCESS_FRIENDS();
  friend class Window;
  friend class TextArea;
  friend class MessageBox;
  friend class List;
  explicit Label(lv_obj_t * object){ m_object = object; }
  Label(Object parent, const Label &);

};



}

#endif // LVGLAPI_LVGL_LABEL_HPP
