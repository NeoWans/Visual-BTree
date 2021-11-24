#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <random>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setFixedSize(800, 600);
  this->setWindowTitle("可视化B树");
  QSize subWindowSize(1600, 900);
  this->subWindow = unique_ptr<QMainWindow>(new QMainWindow(nullptr));
  this->subWindow->setFixedSize(subWindowSize);
  this->subWindow->setWindowTitle("可视化树形");
  this->subWindow->setWindowFlags(Qt::SubWindow);
  this->subWindow->show();
  this->label = unique_ptr<QLabel>(new QLabel(this->subWindow.get()));
  // this->label = unique_ptr<QLabel>(new QLabel(this));
  this->label->setFixedSize(subWindowSize);
  this->pixmap = unique_ptr<QPixmap>(new QPixmap(subWindowSize));
  this->pixmap->fill(Qt::white);
  this->label->setPixmap(*(this->pixmap));
  random_device rd;
  srand(rd());
}

MainWindow::~MainWindow() {
  delete ui;
}

template<typename T>
void MainWindow::dumpBTree(const BTree<T>& tr) {
  tr.dumpToFile();
  this->pixmap->load("BTree.png");
  this->label->setPixmap(*(this->pixmap));
  this->subWindow->show();
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
  cout << "MainWindow mousePressEvent" << endl;
  enum Qt::GlobalColor color;
  if (rand() & 1) color = Qt::GlobalColor::black;
  else color = Qt::GlobalColor::white;
  this->pixmap->fill(color);
  this->label->setPixmap(*(this->pixmap));
}