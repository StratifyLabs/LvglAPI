// Local
#include "LvglRenderer.hpp"
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui_{ std::make_unique<Ui::MainWindow>() }
    , scene_{ new QGraphicsScene(this) }
    , timer_()
{
  ui_->setupUi(this);
  ui_->graphicsView->setScene(scene_);
  connect(&timer_, &QTimer::timeout, ui_->graphicsView, &LvglGraphicsView::tick);
  timer_.setInterval(LvglRenderer::tick_perios_ms);
  timer_.start();
}

MainWindow::~MainWindow() = default;
