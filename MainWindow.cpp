#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setFixedSize(1600, 900);
  this->label = unique_ptr<QLabel>(new QLabel(this));
  this->label->setFixedSize(this->size());
  this->pixmap = unique_ptr<QPixmap>(new QPixmap(this->size()));
  this->label->setPixmap(*(this->pixmap));
  this->pixmap->fill(Qt::white);
  this->painter = unique_ptr<QPainter>(new QPainter(this->pixmap.get()));
  this->painter->drawRect(10, 10, 80, 80);
  this->painter->drawText(20, 30, "你好！");
  this->label->setPixmap(*(this->pixmap));
}

MainWindow::~MainWindow() {
  delete ui;
}
