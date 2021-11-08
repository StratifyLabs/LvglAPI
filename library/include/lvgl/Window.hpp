#ifndef LVGLAPI_LVGL_WINDOW_HPP
#define LVGLAPI_LVGL_WINDOW_HPP

#include "Button.hpp"
#include "Container.hpp"
#include "Label.hpp"

namespace lvgl {


class Window : public ObjectAccess<Window> {
public:

  explicit Window(const char * name = "", lv_coord_t header_height = 15_percent);
  explicit Window(lv_obj_t *object) {m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->window_class; }

  Window &add_button(
    const char *name,
    const void *icon,
    lv_coord_t width,
    void (*setup)(Button) = nullptr) {
    auto object = api()->win_add_btn(m_object, icon, width);
    set_user_data(object, name);
    Button button(object);
    button.add_flag(Flags::event_bubble);
    if (setup) {
      setup(button);
    }
    return *this;
  }

  Window &add_title(const char *name, const char *text, void (*setup)(Label) = nullptr) {
    auto object = api()->win_add_title(m_object, text);
    api()->obj_add_flag(object, LV_OBJ_FLAG_EVENT_BUBBLE);
    set_user_data(object, name);
    if (setup) {
      setup(Label(object));
    }
    return *this;
  }

  API_NO_DISCARD Container get_header() const { return Container(api()->win_get_header(m_object)); }
  API_NO_DISCARD Container get_content() const { return Container(api()->win_get_content(m_object)); }

};

class FileSystemWindow : public ObjectAccess<FileSystemWindow> {
public:

  enum class ExitStatus {
    null,
    closed,
    selected,
    cancelled
  };

  class Data : public UserDataAccess<Data> {
  public:
    explicit Data(const char *name = "") : UserDataBase(name) {}

    API_PMAZ(back_symbol, Data, const char *, LV_SYMBOL_LEFT);
    API_PMAZ(base_path, Data, var::PathString, {});
    API_PMAZ(close_symbol, Data, const char *, LV_SYMBOL_CLOSE);
    API_PMAZ(directory_symbol, Data, const char *, LV_SYMBOL_DIRECTORY);
    API_PMAZ(exit_status, Data, ExitStatus, ExitStatus::null);
    API_PMAZ(file_symbol, Data, const char *, LV_SYMBOL_FILE);

    //members start with is_
    API_PUBLIC_BOOL(Data, select_file, false);
    API_PUBLIC_BOOL(Data, select_folder, false);
    API_PUBLIC_BOOL(Data, show_hidden, false);

    API_PMAZ(path, Data, var::PathString, {});

  };

  explicit FileSystemWindow(Data & data, lv_coord_t header_height = 15_percent);
  explicit FileSystemWindow(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->window_class; }


private:
  struct Names {
    static constexpr auto ok_button = "OkButton";
    static constexpr auto back_button = "BackButton";
    static constexpr auto entry_list = "EntryList";
    static constexpr auto tile_view = "TileView";
    static constexpr auto file_browser_window = "FileBrowser";
    static constexpr auto window_title = "WindowTitle";
    static constexpr auto file_details_table = "FileDetails";
    static constexpr auto home_button = "HomeButton";
    static constexpr auto select_button = "SelectButton";
    static constexpr auto cancel_button = "CancelButton";
    static constexpr auto show_hidden_checkbox = "ShowHidden";
  };

  class TileData : public UserDataAccess<TileData> {
  public:
    explicit TileData(const char *path) : UserDataBase(""), m_path(path) {}

  private:
    API_AC(TileData, var::PathString, path);
  };

  API_NO_DISCARD Container get_header() const { return Container(api()->win_get_header(m_object)); }
  API_NO_DISCARD Container get_content() const { return Container(api()->win_get_content(m_object)); }

  static void configure_details(Container container);
  static void configure_list(Container container);

  static var::PathString get_next_path(const var::PathString & path, const char *entry);

  static void set_back_button_label(const Window &window, const char *symbol);
  static Label get_title_label(const Window &window);
  static Window get_window(Object object) { return object.find_parent<Window>(); }
};

} // namespace lvgl

#endif // LVGLAPI_LVGL_WINDOW_HPP
