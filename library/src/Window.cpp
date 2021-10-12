#include <fs/FileSystem.hpp>
#include <fs/Path.hpp>

#include "lvgl/Draw.hpp"
#include "lvgl/Event.hpp"
#include "lvgl/Image.hpp"
#include "lvgl/List.hpp"
#include "lvgl/Table.hpp"
#include "lvgl/TileView.hpp"
#include "lvgl/Window.hpp"

using namespace lvgl;

Window::Window(Object parent, const Window &options) {
  m_object = api()->win_create(parent.object(), options.m_construct->header_height());
  get_header().add_flag(Flags::event_bubble);
  get_content().add_flag(Flags::event_bubble);
}

FileSystemWindow::FileSystemWindow(Object parent, const FileSystemWindow &options) {
  m_object = api()->win_create(parent.object(), options.m_construct->header_height());
  get_header().add_flag(Flags::event_bubble);
  get_content().add_flag(Flags::event_bubble);

  set_user_data(m_object, options.initial_name());

  auto *user_data =
    reinterpret_cast<FileSystemWindow::FileSystemData *>(options.initial_context());

  user_data->set_path(user_data->base_path());

  auto window = Container(m_object).get<Window>();

  window.clear_flag(Window::Flags::scrollable)
    .add_title(
      window_title_name, user_data->base_path(),
      [](Label &label) { label.set_left_padding(10); })
    .add_button(back_button_name, user_data->close_symbol(), size_from_content)
    .set_width(100_percent)
    .set_height(100_percent)
    .add_event_callback(
      EventCode::clicked,
      [](lv_event_t *lv_event) {
        const Event event(lv_event);
        if (event.target().name() == back_button_name) {

          auto window = event.current_target<Window>();
          auto *file_system_data = window.user_data<FileSystemData>();

          if (file_system_data->path() != file_system_data->base_path()) {

            file_system_data->set_path(fs::Path::parent_directory(file_system_data->path()));
            if (file_system_data->path().is_empty()) {
              file_system_data->set_path(file_system_data->base_path());
            }

            window.find<Label>(window_title_name)
              .set_text_static(file_system_data->path());
            event.current_target().find<TileView>(tile_view_name).go_backward();

            const auto is_close = file_system_data->path() == file_system_data->base_path();
            set_back_button_label(
              window, is_close ? file_system_data->close_symbol() : file_system_data->back_symbol());

          } else {
            // exit signal
            file_system_data->set_path("");
            Event::send(window.get_parent(), EventCode::exited);
          }
        }
      })
    .add(TileView(tile_view_name));

  auto tile_view = window.find<TileView>(tile_view_name);

  tile_view.set_width(100_percent)
    .set_height(100_percent)
    .add_tile(
      TileData::create("").set_path(user_data->path()),
      TileView::Location().set_column(0), configure_list);
}

void FileSystemWindow::set_back_button_label(const Window &window, const char *symbol) {
  auto result = window.find(back_button_name).get_child(0).get<Image>();
  result.set_source(symbol);
}

Label FileSystemWindow::get_title_label(const Window &window) {
  return window.find<Label>(window_title_name);
}

void FileSystemWindow::configure_details(Container &container) {

  container
    .add_event_callback(
      EventCode::entered,
      [](lv_event_t *e) {
        const Event event(e);
        auto *tile_data = event.target().user_data<TileData>();
        auto window = get_window(event.target());
        auto *fs_data = window.user_data<FileSystemData>();

        set_back_button_label(window, fs_data->back_symbol());
        get_title_label(window).set_text(tile_data->path());
      })
    .add(Table(file_details_table_name).configure([](Table &table) {
      auto *tile_data = table.get_parent().user_data<TileData>();

      const auto width = Container::active_screen().get_width();
      const auto info = fs::FileSystem().get_info(tile_data->path());
      const auto file_type = info.is_file() ? "File" : "Device";

      table.set_width(100_percent)
        .set_height(100_percent)
        .set_column_count(2)
        .set_row_count(4)
        .set_column_width(0, width / 2)
        .set_column_width(1, width / 2)
        .set_cell_value(Table::Cell().set_column(0).set_row(0), "Type")
        .set_cell_value(Table::Cell().set_column(0).set_row(1), "Size")
        .set_cell_value(Table::Cell().set_column(0).set_row(2), "Mode")
        .set_cell_value(Table::Cell().set_column(0).set_row(3), "Owner")
        .set_cell_value(Table::Cell().set_column(1).set_row(0), file_type)
        .set_cell_value(
          Table::Cell().set_column(1).set_row(1), var::NumberString(info.size()))
        .set_cell_value(
          Table::Cell().set_column(1).set_row(2),
          var::NumberString(info.permissions().permissions(), "0%o"))
        .set_cell_value(
          Table::Cell().set_column(1).set_row(3), info.owner() ? "user" : "root")
        .add_event_callback(EventCode::draw_part_begin, [](lv_event_t *e) {
          const Event event(e);
          Draw draw(event.parameter<lv_obj_draw_part_dsc_t *>());

          /*If the cells are drawn...*/
          if (draw.part() == Part::items) {
            uint32_t row = draw.id() / 2;

            /*Make every 2nd row grayish*/
            if ((row % 2) == 0) {
              auto rect = draw.get_rectangle();
              const auto background_color = rect.background_color();
              const auto mix_color =
                Color::get_palette(Palette::grey).mix(background_color, MixRatio::x10);
              rect.set_background_color(mix_color).set_background_opacity(Opacity::cover);
            }
          }
        });
    }));
}

void FileSystemWindow::configure_list(Container &container) {
  // load the path

  container
    .add_event_callback(
      EventCode::entered,
      [](lv_event_t *e) {
        const Event event(e);
        auto *tile_data = event.target().user_data<TileData>();
        auto window = get_window(event.target());
        get_title_label(window).set_text(tile_data->path());

        auto *fs_data = window.user_data<FileSystemData>();
        if (fs_data->path() != fs_data->base_path()) {
          set_back_button_label(window, fs_data->back_symbol());
        }
      })
    .add(FormList(FormList::FormData::create()).configure([](FormList &list) {
      list.set_top_padding(0)
        .set_scroll_mode(ScrollBarMode::active)
        .set_border_width(0)
        .set_radius(0)
        .set_bottom_padding(0)
        .set_width(100_percent)
        .set_height(100_percent)
        .add_event_callback(EventCode::clicked, [](lv_event_t *e) {
          const Event event(e);
          const char *entry_name = event.target().name();
          if (entry_name != entry_list_name) {
            auto list = event.current_target<List>();
            const auto entry_value = list.get_button_text(event.target());

            auto *tile_data = list.get_parent().user_data<TileData>();

            auto window = get_window(event.target());
            auto *file_browser_data = window.user_data<FileSystemData>();

            const auto next_path = get_next_path(tile_data->path(), entry_value);
            const auto info = fs::FileSystem().get_info(next_path);

            // clicked a directory or a file?
            auto tile_view = window.find<TileView>(tile_view_name);
            if (info.is_directory()) {
              file_browser_data->set_path(next_path);
              tile_view.go_forward(TileData::create(next_path), configure_list);
            } else {
              file_browser_data->set_path(next_path);
              if (file_browser_data->is_select_file()) {
                Event::send(window.get_parent(), EventCode::exited);
              } else {
                tile_view.go_forward(TileData::create(next_path), configure_details);
              }
            }
          }
        });

      auto *file_system_data = get_window(list).user_data<FileSystemData>();

      // add items in the director to the list
      const auto &path = file_system_data->path();
      const auto file_list = fs::FileSystem().read_directory(path);
      for (const auto &item : file_list) {
        const auto full_path = get_next_path(path, item);
        {
          api::ErrorScope es;
          const auto info = fs::FileSystem().get_info(full_path);
          const auto *symbol = info.is_directory() ? file_system_data->directory_symbol()
                                                   : file_system_data->file_symbol();
          const auto item_type = file_system_data->is_select_file() && info.is_file()
                                   ? FormList::ItemType::string
                                   : FormList::ItemType::navigation;
          list.add_item(
            FormList::ItemData::create(item).set_symbol(symbol).set_type(item_type));
        }
      }
    }));
}
