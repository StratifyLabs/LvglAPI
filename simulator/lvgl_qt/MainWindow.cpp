// Local
#include <api/api.hpp>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFile>

#include "LvglGraphicsView.hpp"
#include "LvglRenderer.hpp"
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  auto * scene = new QGraphicsScene(this);
  auto * view = new LvglGraphicsView(scene, this);
  auto * timer = new QTimer();

  m_group = lvgl::Group::create();
  lv_indev_set_group(view->keyboard_device(), m_group.group());


  connect(timer, &QTimer::timeout, view, &LvglGraphicsView::tick);
  setCentralWidget(view);
  timer->setInterval(LvglRenderer::tick_perios_ms);
  timer->start();
}

var::Data MainWindow::get_assets(const var::StringView path){
  QFile file(var::PathString(path).cstring());
  if (file.open(QFile::ReadOnly) == false) {
    printf("failed to open\n");
  }
  auto byte_array = file.readAll();
  file.close();
  var::Data result;
  result.resize(byte_array.size());
  var::View(result).copy(var::View(byte_array.data(), byte_array.size()));
  return result;
}

MainWindow::~MainWindow(){

}
