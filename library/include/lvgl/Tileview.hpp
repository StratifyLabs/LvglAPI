#ifndef LVGLAPI_LVGL_TILEVIEW_HPP
#define LVGLAPI_LVGL_TILEVIEW_HPP

#include "Object.hpp"

namespace lv {

class TileView : public ObjectAccess<TileView>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  TileView(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_TILEVIEW_HPP
