#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "MainWindow.h"
#include "ui_MainWindow.h"
const vector<string> MainWindow::operationStr = {"构造", "清空", "插入", "删除"};
MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setGeometry(5, 200, 0, 0);
  this->setFixedSize(300, 500);
  this->setWindowTitle("B树 输入");
  QSize subWindowSize(1600, 900);
  this->subWindow = unique_ptr<QMainWindow>(new QMainWindow(nullptr));
  this->subWindow->setGeometry(310, 0, 0, 0);
  this->subWindow->setFixedSize(subWindowSize);
  this->subWindow->setWindowTitle("可视化树形");
  this->subWindow->setWindowFlags(Qt::SubWindow);
  this->label = unique_ptr<QLabel>(new QLabel(this->subWindow.get()));
  this->label->setFixedSize(subWindowSize);
  this->label->setScaledContents(true);
  this->pixmap = unique_ptr<QPixmap>(new QPixmap(subWindowSize));
  this->pixmap->fill(Qt::white);
  this->label->setPixmap(*(this->pixmap));
  this->subWindow->show();
  this->operationMenu = unique_ptr<QComboBox>(new QComboBox(this));
  for (const auto& str : this->operationStr)
    this->operationMenu->addItem(str.c_str());
  this->submitButton = unique_ptr<QPushButton>(new QPushButton(this));
  this->submitButton->setText("提交");
  this->btree = nullptr;
  this->input = unique_ptr<QTextEdit>(new QTextEdit(this));
  this->input->setText("");
  connect(this->submitButton.get(), &QPushButton::clicked, this, [&]() {
    procInput(this->operationMenu->currentIndex(), (this->input->toPlainText()).toStdString());
    dumpBTree(this->btree.get());
    });
  this->input->setGeometry(0, 0, 300, 450);
  this->operationMenu->setGeometry(10, 460, 135, 30);
  this->submitButton->setGeometry(155, 460, 135, 30);
}

MainWindow::~MainWindow() {
  delete ui;
}

template<typename T>
void MainWindow::dumpBTree(BTree<T>* btree) {
  if (btree == nullptr) this->pixmap->fill(Qt::white);
  else {
    btree->dumpToFile();
    this->pixmap->load("BTree.png");
  }
  this->label->setPixmap(*(this->pixmap));
  this->subWindow->show();
}

void MainWindow::procInput(int op, const string& str) {
  istringstream iss(str);
  switch (op) {
  case 0: {
    int m; iss >> m;
    this->btree = unique_ptr<BTree<int>>(new BTree<int>(m));
    goto BTREE_INSERT;
    break;
  }
  case 1: {
    this->btree.reset();
    break;
  }
  case 2: {
BTREE_INSERT:
    if (this->btree == nullptr) break;
    int x;
    while (iss >> x)
      this->btree->insert(x);
    break;
  }
  case 3: {
    if (this->btree == nullptr) break;
    // int x;
    // while (iss >> x)
    //   this->btree->remove(x);
    break;
  }
  default: break;
  }
}
