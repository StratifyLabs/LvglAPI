#ifndef LVGLAPI_LVGL_ARC_HPP
#define LVGLAPI_LVGL_ARC_HPP

#include "Object.hpp"

namespace lv {

class Arc : public ObjectAccess<Arc> {
public:
  enum class Mode {
    normal = LV_ARC_MODE_NORMAL,
    reverse = LV_ARC_MODE_REVERSE,
    symmetrical = LV_ARC_MODE_SYMMETRICAL
  };

  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };

  Arc(Object parent, const Create & options);

  Arc & set_start_angle(u16 value){
    api()->arc_set_start_angle(m_object, value);
    return *this;
  }

  u16 get_start_angle() const {
    return api()->arc_get_angle_start(m_object);
  }

  Arc & set_end_angle(u16 value){
    api()->arc_set_end_angle(m_object, value);
    return *this;
  }

  u16 get_end_angle() const {
    return api()->arc_get_angle_end(m_object);
  }

  Arc & set_angles(u16 start, u16 stop){
    api()->arc_set_angles(m_object, start, stop);
    return *this;
  }

  Arc & set_background_start_angle(u16 value){
    api()->arc_set_bg_start_angle(m_object, value);
    return *this;
  }

  u16 get_background_start_angle() const {
    return api()->arc_get_bg_angle_start(m_object);
  }

  Arc & set_background_end_angle(u16 value){
    api()->arc_set_bg_start_angle(m_object, value);
    return *this;
  }

  u16 get_background_end_angle() const {
    return api()->arc_get_bg_angle_end(m_object);
  }

  Arc & set_background_angles(u16 start, u16 stop){
    api()->arc_set_bg_angles(m_object, start, stop);
    return *this;
  }

  Arc & set_rototion(u16 value){
    api()->arc_set_rotation(m_object, value);
    return *this;
  }

  Arc & set_rototion(Mode value){
    api()->arc_set_mode(m_object, static_cast<lv_arc_mode_t>(value));
    return *this;
  }


  Arc & set_value(u16 value){
    api()->arc_set_value(m_object, value);
    return *this;
  }

  u16 get_value() const {
    return api()->arc_get_value(m_object);
  }

};

}

#endif // LVGLAPI_LVGL_ARC_HPP
