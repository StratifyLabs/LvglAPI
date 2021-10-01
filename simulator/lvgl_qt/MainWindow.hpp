#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

// Standard
#include <memory>

// 3rd Party
#include <QMainWindow>
#include <QTimer>

#include <lvgl/Group.hpp>

#include <var/Data.hpp>
#include <var/StringView.hpp>

class MainWindow final : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

  lvgl::Group & keyboard_group(){
    return m_group;
  }

  var::Data get_assets(const var::StringView path);

private:
  lvgl::Group m_group;

};

#endif // MAINWINDOW_HPP
