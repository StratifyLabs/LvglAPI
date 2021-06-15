#ifndef LVGLAPI_LVGL_THEME_HPP
#define LVGLAPI_LVGL_THEME_HPP

#include "Object.hpp"

namespace lv {

class Theme : public Api {
public:
  Theme();

  Theme& apply(Object object){
    api()->theme_apply(object.object());
    return *this;
  }



private:
  lv_theme_t * m_theme;
};

}

#endif // LVGLAPI_LVGL_THEME_HPP
