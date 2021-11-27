#include "lvgl/Image.hpp"

using namespace lvgl;

Image::Image(const char *name) {
  m_object = api()->img_create(screen_object());
  set_user_data(m_object, name);
}

Image::Info Image::find_image(const char *name, const Size size) {
  const auto count = []() {
    int offset = 0;
    while (api()->get_image(offset) != nullptr) {
      offset++;
    }
    return offset;
  }();

  if (count == 0) {
    return {};
  }

  const lvgl_api_image_descriptor_t *descriptor_list[count];
  for (auto offset : api::Index(count)) {
    descriptor_list[offset] = api()->get_image(offset);
  }

  for (u16 i = 0; i < count; i++) {
    const Info image_info(descriptor_list[i]->name, descriptor_list[i]->image);
    // check if name is compatible

    if (var::StringView(image_info.name()).find(name) == 0) {
      const auto is_size_ok = [&]() {
        if (size.width() == 0) {
          return true;
        }
        if (image_info.width() > size.width()) {
          return false;
        }

        if (image_info.height() > size.height()) {
          return false;
        }

        return true;
      }();

      if (is_size_ok) {
        return image_info;
      }
    }
  }
  return {};
}
