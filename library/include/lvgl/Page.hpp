#ifndef LVGLAPI_LVGL_PAGE_HPP
#define LVGLAPI_LVGL_PAGE_HPP

#include "ObjectAccess.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Page : public ObjectAccess<Page>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  Page(Object parent, const Create & options);

private:
  OBJECT_ACCESS_FRIENDS();
};

}

#endif // LVGLAPI_LVGL_PAGE_HPP
