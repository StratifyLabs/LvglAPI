#include <fs/ViewFile.hpp>

#include "lvgl/Bar.hpp"
#include "lvgl/Event.hpp"
#include "lvgl/TextArea.hpp"

using namespace lvgl;

TextArea::TextArea(const char *name) {
  m_object = api()->textarea_create(screen_object());
  set_user_data(m_object, name);
}

FileTextArea::FileTextArea(Data &data) {
  m_object = api()->textarea_create(screen_object());
  set_user_data(m_object, data.cast_as_name());

  set_scroll_mode(ScrollBarMode::active);

  API_ASSERT(data.file() != nullptr);

  const auto file_size = data.file()->size();

  if (file_size > data.m_buffer.size()) {
    // add a progress bar
#if 0
    parent.get<Container>().add_object(Bar(progress_bar_name)
                                         .set_height(20)
                                         .set_width(100_percent)
                                         .set_alignment(Alignment::bottom_middle));
#endif

    const auto pages = file_size / data.m_buffer.size() + 1;
    data.set_progress_size(1000 / pages);
    data.set_progress_start(0);
#if 0
    parent.find<Bar>(progress_bar_name)
      .set_mode(Bar::Mode::range)
      .set_start_value(0)
      .set_value(data.progress_size())
      .set_range(Range().set_maximum(1000));
#endif
  }

  // load file line by line to buffer

  static auto update_text = [](FileTextArea &file_text_area) {
    auto *data = file_text_area.user_data<Data>();
    API_ASSERT(data != nullptr);

    auto &file = *data->file();
    size_t bytes_read = 0;
    fs::ViewFile view_file(data->m_buffer);
    bool is_full = false;

    do {
      int location = file.location();
      auto line = file.get_line<var::GeneralString>();
      if (line.is_empty()) {
        is_full = true;
      } else {
        const auto bytes_remaining = data->m_buffer.size() - bytes_read;
        if (line.length() * 4 < bytes_remaining) {
          bytes_read += line.length();
          view_file.write(line.string_view());
        } else {
          file.seek(location);
          is_full = true;
        }
      }
    } while (!is_full);

    if (bytes_read > 0) {
      data->m_buffer.at_char(bytes_read - 1) = 0;
      file_text_area.set_text("")
        .set_text_static(data->m_buffer.to_const_char())
        .update_layout();
    }
  };

  add_event_callback(EventCode::scroll_end, [](lv_event_t *e) {
    auto object = Event(e).target();
    if (object.get_scroll_bottom() < -50) {
      printf("scroll down\n");
      auto file_text_area = object.get<FileTextArea>();
      update_text(file_text_area);
    }
  });

  add_event_callback(EventCode::scroll_begin, [](lv_event_t *e) {
    auto object = Event(e).target();
    if (object.get_scroll_top() < -50) {
      printf("scroll up\n");

      auto file_text_area = object.get<FileTextArea>();
      auto *data = file_text_area.user_data<Data>();
      const auto location = data->file()->location();
      const auto jump_size = data->m_buffer.size() * 2;
      if (location > int(jump_size)) {
        data->file()->seek(location - jump_size);
        data->file()->get_line<var::GeneralString>();
      } else {
        data->file()->seek(0);
      }
      update_text(file_text_area);
    }
  });

  update_text(*this);
}
