#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

// Standard
#include <memory>

// 3rd Party
#include <QMainWindow>

#include <lvgl/Group.hpp>

#include <var/Data.hpp>
#include <var/StringView.hpp>

class MainWindow final : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow();

  lvgl::Group & keyboard_group(){
    return m_group;
  }

  var::Data get_assets(const var::StringView path);

  static lvgl::WheelEvent get_wheel_event_callback(void * context){
    return reinterpret_cast<MainWindow*>(context)->get_wheel_event();
  }

  void * wheel_event_context(){
    return this;
  }

private:
  lvgl::Group m_group;

  void * m_view = nullptr;
  lvgl::WheelEvent get_wheel_event();

  void resizeEvent(QResizeEvent * event);

};

#endif // MAINWINDOW_HPP
