#ifndef LVGLAPI_LVGL_WINDOW_HPP
#define LVGLAPI_LVGL_WINDOW_HPP

#include "Button.hpp"
#include "Container.hpp"
#include "Label.hpp"

namespace lvgl {
OBJECT_ACCESS_FORWARD_FRIENDS();

class Window : public ObjectAccess<Window> {
public:
  class Construct {
    API_AF(Construct, lv_coord_t, header_height, 15_percent);
  };

  explicit Window(const char *name, const Construct &options)
    : ObjectAccess(name), m_construct(&options) {}
  explicit Window(const UserData &context, const Construct &options)
    : ObjectAccess(context.cast_as_name()), m_construct(&options) {}

  static const lv_obj_class_t *get_class() { return api()->window_class; }

  Window &add_button(
    const char *name,
    const void *icon,
    lv_coord_t width,
    void (*add)(Button &) = nullptr) {
    auto object = api()->win_add_btn(m_object, icon, width);
    set_user_data(object, name);
    Button button(object);
    button.add_flag(Flags::event_bubble);
    if (add) {
      add(button);
    }
    return *this;
  }

  Window &add_button(
    const UserData &context,
    const void *icon,
    lv_coord_t width,
    void (*add)(Button &) = nullptr) {
    return add_button(context.cast_as_name(), icon, width, add);
  }

  Window &add_title(const char *name, const char *text, void (*add)(Label &) = nullptr) {
    auto object = api()->win_add_title(m_object, text);
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    set_user_data(object, name);
    if (add) {
      Label label(object);
      add(label);
    }
    return *this;
  }

  Window &
  add_title(const UserData &context, const char *text, void (*add)(Label &) = nullptr) {
    return add_title(context.cast_as_name(), text, add);
  }

  Container get_header() const { return Container(api()->win_get_header(m_object)); }
  Container get_content() const { return Container(api()->win_get_content(m_object)); }

private:
  OBJECT_ACCESS_FRIENDS();
  explicit Window(lv_obj_t *object) { m_object = object; }
  Window(Object parent, const Window &options);

  const Construct *m_construct;
};


class FileSystemWindow : public ObjectAccess<FileSystemWindow> {
public:
  class Construct {
    API_AF(Construct, lv_coord_t, header_height, 15_percent);
  };


  class FileSystemData : public UserDataAccess<FileSystemData> {
  public:
    FileSystemData(const char * name) : UserDataBase(name){}

  private:
    API_AC(FileSystemData,var::PathString,base_path);
    API_AC(FileSystemData,var::PathString,path);
    API_AB(FileSystemData,select_file,false);
    API_AF(FileSystemData,const char *, directory_symbol, LV_SYMBOL_DIRECTORY);
    API_AF(FileSystemData,const char *, file_symbol, LV_SYMBOL_FILE);
    API_AF(FileSystemData,const char *, back_symbol, LV_SYMBOL_LEFT);
    API_AF(FileSystemData,const char *, close_symbol, LV_SYMBOL_CLOSE);
  };

  explicit FileSystemWindow(const UserData &context, const Construct &options)
    : ObjectAccess(context.cast_as_name()), m_construct(&options) {}

  static const lv_obj_class_t *get_class() { return api()->window_class; }

  static constexpr auto back_button_name = "BackButton";
  static constexpr auto entry_list_name = "EntryList";
  static constexpr auto tile_view_name = "TileView";
  static constexpr auto file_browser_window = "FileBrowser";
  static constexpr auto window_title_name = "WindowTitle";
  static constexpr auto file_details_table_name = "FileDetails";

private:

  class TileData : public UserDataAccess<TileData> {
  public:
    TileData(const char *path) : UserDataBase(""), m_path(path) {}

  private:
    API_AC(TileData, var::PathString, path);
  };

  OBJECT_ACCESS_FRIENDS();
  explicit FileSystemWindow(lv_obj_t *object) { m_object = object; }
  FileSystemWindow(Object parent, const FileSystemWindow &options);

  Container get_header() const { return Container(api()->win_get_header(m_object)); }
  Container get_content() const { return Container(api()->win_get_content(m_object)); }

  const Construct *m_construct;

  static void configure_details(Container &container);
  static void configure_list(Container &container);

  static var::PathString get_next_path(const var::PathString path, const char *entry) {
    if (path == "/") {
      return var::PathString(path).append(entry);
    }
    return path / entry;
  }

  static void set_back_button_label(const Window &window, const char * symbol);
  static Label get_title_label(const Window & window);
  static Window get_window(Object object){
    return object.find_parent<Window>();
  }
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_WINDOW_HPP
