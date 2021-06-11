#ifndef LVGLAPI_LVGL_TABLE_HPP
#define LVGLAPI_LVGL_TABLE_HPP

#include "Object.hpp"

namespace lv {

class Table : public ObjectAccess<Table>
{
public:
  class Create : public CreateAccess<Create> {
  public:
    Create(const char * name) : CreateAccess(name){}
  };
  Table(Object parent, const Create & options);
};

}

#endif // LVGLAPI_LVGL_TABLE_HPP
