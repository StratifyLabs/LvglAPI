#include <fs/FileSystem.hpp>
#include <fs/Path.hpp>

#include "lvgl/Checkbox.hpp"
#include "lvgl/Draw.hpp"
#include "lvgl/Event.hpp"
#include "lvgl/Image.hpp"
#include "lvgl/Line.hpp"
#include "lvgl/List.hpp"
#include "lvgl/Table.hpp"
#include "lvgl/TileView.hpp"
#include "lvgl/Window.hpp"

#ifdef __win32
#define ROOT_DRIVE "C:/"
#else
#define ROOT_DRIVE "/"
#endif

using namespace lvgl;

Window::Window(const char *name, lv_coord_t header_height) {
  m_object = api()->win_create(screen_object(), header_height);
  set_user_data(m_object, name);
  get_header().add_flag(Flags::event_bubble);
  get_content().add_flag(Flags::event_bubble);
}

FileSystemWindow::FileSystemWindow(Data &data, lv_coord_t header_height) {
  m_object = api()->win_create(screen_object(), header_height);
  get_header().add_flag(Flags::event_bubble);
  get_content().add_flag(Flags::event_bubble);

  set_user_data(m_object, data.cast_as_name());

  data.set_path(data.base_path());
  printf("load path %s\n", data.base_path().cstring());

  auto window = Container(m_object).get<Window>();

  window.clear_flag(Window::Flags::scrollable)
    .add_title(Names::window_title, data.base_path(), [](Label label) {
      label.set_left_padding(10);
    });

  window.add_button(Names::back_button, data.close_symbol(), size_from_content)
    .fill()
    .add_event_callback(
      EventCode::clicked,
      [](lv_event_t *lv_event) {
        const Event event(lv_event);
        const auto target_name = event.target().name();
        auto window = event.current_target<Window>();
        auto *file_system_data = window.user_data<Data>();
        if (target_name == Names::back_button) {

          if (file_system_data->path() != file_system_data->base_path()) {

            file_system_data->set_path(
              fs::Path::parent_directory(file_system_data->path()));
            if (file_system_data->path().is_empty()) {
              file_system_data->set_path(file_system_data->base_path());
            }

            get_title_label(window).set_text_static(file_system_data->path());
            event.current_target().find<TileView>(Names::tile_view).go_backward();

            const auto is_close =
              file_system_data->path() == file_system_data->base_path();
            set_back_button_label(
              window, is_close ? file_system_data->close_symbol()
                               : file_system_data->back_symbol());

          } else {
            // exit signal
            file_system_data->set_path("");
            Event::send(window.get_parent(), EventCode::exited);
          }
        } else if (target_name == Names::ok_button) {
          Event::send(window.get_parent(), EventCode::exited);
        } else if (target_name == Names::select_button) {
          Event::send(window.get_parent(), EventCode::exited);
        } else if (target_name == Names::cancel_button) {
          file_system_data->set_path("");
          Event::send(window.get_parent(), EventCode::exited);
        } else if (target_name == Names::home_button) {
          auto tile_view = event.current_target().find<TileView>(Names::tile_view);
          tile_view.set_tile(TileView::Location());
          auto home_tile = tile_view.get_tile(TileView::Location()).get<Container>();

          const auto *home = getenv("HOME");
          const var::PathString folder = home != nullptr ? home : ROOT_DRIVE;

          file_system_data->set_path(folder);

          get_title_label(window).set_text_static(file_system_data->path());
          auto *tile_data = home_tile.user_data<TileData>();
          tile_data->set_path(file_system_data->path());
          configure_list(home_tile.clean());
        }
      })
    .get_content()
    .add_flag(Flags::event_bubble)
    .add(Column()
           .add_flag(Flags::event_bubble)
           .fill()
           .set_row_padding(0)
           .add(TileView(Names::tile_view).fill_width().set_flex_grow())
           .add(Row()
                  .add_flag(Flags::event_bubble)
                  .fill_width()
                  .set_height(Row::size_from_content)
                  .set_column_padding(20)
                  .set_padding(20)
                  .set_flex_align(SetFlexAlign().set_main(FlexAlign::end))
                  .add(Button(Names::home_button)
                         .add_static_label(LV_SYMBOL_HOME)
                         .add_flag(Flags::event_bubble))
                  .add(Button(Names::select_button)
                         .add_static_label("Select")
                         .add_flag(Flags::event_bubble))
                  .add(Button(Names::cancel_button)
                         .add_static_label("Cancel")
                         .add_flag(Flags::event_bubble))))
    .set_padding(0);

  // configure_list() requires the view to be complete
  window.find<TileView>(Names::tile_view)
    .add_tile(
      TileData::create("").set_path(data.path()).cast_as_name(),
      TileView::Location().set_column(0), configure_list);
}

void FileSystemWindow::set_back_button_label(const Window &window, const char *symbol) {
  auto result = window.find(Names::back_button).get_child(0).get<Image>();
  result.set_source(symbol);
}

Label FileSystemWindow::get_title_label(const Window &window) {
  return window.find<Label>(Names::window_title);
}

void FileSystemWindow::configure_details(Container container) {

  container
    .add_event_callback(
      EventCode::entered,
      [](lv_event_t *e) {
        const Event event(e);
        auto *tile_data = event.target().user_data<TileData>();
        auto window = get_window(event.target());
        auto *fs_data = window.user_data<Data>();

        set_back_button_label(window, fs_data->back_symbol());
        get_title_label(window).set_text(tile_data->path());
      })
    .add(Table(Names::file_details_table).setup([](Table table) {
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

void FileSystemWindow::configure_list(Container container) {
  // load the path

  container
    .add_event_callback(
      EventCode::entered,
      [](lv_event_t *e) {
        const Event event(e);
        auto *tile_data = event.target().user_data<TileData>();
        auto window = get_window(event.target());
        get_title_label(window).set_text(tile_data->path());

        auto *fs_data = window.user_data<Data>();
        if (fs_data->path() != fs_data->base_path()) {
          set_back_button_label(window, fs_data->back_symbol());
        }
      })
    .add(FormList(FormList::Data::create()).setup([](FormList list) {
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
          if (entry_name != Names::entry_list) {
            auto list = event.current_target<List>();
            const auto entry_value = list.get_button_text(event.target());

            auto *tile_data = list.get_parent().user_data<TileData>();

            auto window = get_window(event.target());
            auto *file_browser_data = window.user_data<Data>();

            const auto next_path = get_next_path(tile_data->path(), entry_value);
            const auto info = fs::FileSystem().get_info(next_path);

            // clicked a directory or a file?
            auto tile_view = window.find<TileView>(Names::tile_view);
            if (info.is_directory()) {
              file_browser_data->set_path(next_path);
              tile_view.go_forward(
                TileData::create(next_path).cast_as_name(), configure_list);
            } else {
              file_browser_data->set_path(next_path);
              if (file_browser_data->is_select_file()) {
                Event::send(window.get_parent(), EventCode::exited);
              } else {
                tile_view.go_forward(
                  TileData::create(next_path).cast_as_name(), configure_details);
              }
            }
          }
        });

      auto *file_system_data = get_window(list).user_data<Data>();

      // add items in the director to the list
      const auto &path = file_system_data->path();
      auto is_exclude = [](const var::StringView name, void *data) {
        auto *file_system_data = reinterpret_cast<Data *>(data);

        if (file_system_data->is_show_hidden() == false) {
          if (name.length() && name.at(0) == '.') {
            return fs::FileSystem::IsExclude::yes;
          }
        }

        if (file_system_data->is_select_folder()) {
          const auto info = fs::FileSystem().get_info(file_system_data->path() / name);
          if (info.is_directory() == false) {
            return fs::FileSystem::IsExclude::yes;
          }
        }

        return fs::FileSystem::IsExclude::no;
      };

      const auto file_list =
        fs::FileSystem()
          .read_directory(
            path, fs::FileSystem::IsRecursive::no, is_exclude, file_system_data)
          .sort(fs::PathList::ascending);
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

          list.add_item(FormList::ItemData::create(item.cstring())
                          .set_symbol(symbol)
                          .set_type(item_type));
        }
      }
    }));
}
