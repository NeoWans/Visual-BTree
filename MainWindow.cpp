#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setFixedSize(800, 600);
  this->subWindow = unique_ptr<QWidget>(new QWidget(this));
  this->subWindow->setFixedSize(1600, 900);
  this->subWindow->show();
  this->label = unique_ptr<QLabel>(new QLabel(this->subWindow.get()));
  this->label->setFixedSize(this->subWindow->size());
  this->pixmap = unique_ptr<QPixmap>(new QPixmap(this->size()));
  this->pixmap->fill(Qt::white);
  // this->painter = unique_ptr<QPainter>(new QPainter(this->pixmap.get()));
  this->label->setPixmap(*(this->pixmap));
}

MainWindow::~MainWindow() {
  delete ui;
}

template<typename T>
void MainWindow::dumpBTree(const BTree<T>& tr) {
  tr.dumpToFile();
  this->pixmap->load("BTree.png");
  this->label->setPixmap(*(this->pixmap));
}