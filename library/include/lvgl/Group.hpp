#ifndef LVGLAPI_GROUP_HPP
#define LVGLAPI_GROUP_HPP

#include "Object.hpp"

namespace lvgl {

class Group : public Api {
public:

  static Group create();

  Group& add_object(Object object){
    api()->group_add_obj(m_group, object.object());
    return *this;
  }

  lv_group_t * group(){
    return m_group;
  }

private:
  lv_group_t *m_group = nullptr;
};

} // namespace lvgl

#endif // LVGLAPI_GROUP_HPP
