#ifndef LVGLAPI_LVGL_CANVAS_HPP
#define LVGLAPI_LVGL_CANVAS_HPP

#include "ObjectAccess.hpp"

#include "Image.hpp"

namespace lvgl {


class Canvas : public ObjectAccess<Canvas> {
public:
  LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(Canvas);

  static const lv_obj_class_t * get_class(){
    return api()->canvas_class;
  }

  Canvas& set_buffer(void * buf, const Size size, ColorFormat color_format);
  Canvas& set_pixel(const Point & point, Color color);
  Canvas& set_pixel(const Point & point, Opacity opacity);
  Color get_pixel(const Point& point) const;


  ImageDescriptor get_image_descriptor() const;

};

} // namespace lvgl

#endif // LVGLAPI_LVGL_CANVAS_HPP
