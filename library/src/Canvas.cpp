#include "lvgl/Canvas.hpp"

using namespace lvgl;

LVGL_OBJECT_ASSERT_SIZE(Canvas);


Canvas::Canvas(const char * name){
  m_object =
    lv_canvas_create(screen_object());
  set_user_data(m_object,name);
}

Canvas &Canvas::set_buffer(void *buf, const Size size, ColorFormat color_format) {
    api()->canvas_set_buffer(m_object, buf, size.width(), size.height(), lv_img_cf_t(color_format));
    return *this;
}

ImageDescriptor Canvas::get_image_descriptor() const {
  return ImageDescriptor(api()->canvas_get_img(m_object));
}

Canvas &Canvas::set_pixel(const Point &point, Color color) {
  api()->canvas_set_px_color(m_object, point.x(), point.y(), color.get_color());
  return *this;
}

Canvas &Canvas::set_pixel(const Point &point, Opacity opacity) {
  api()->canvas_set_px_opa(m_object, point.x(), point.y(), lv_opa_t(opacity));
  return *this;
}
