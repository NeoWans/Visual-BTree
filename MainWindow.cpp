#include "MainWindow.h"
#include "ui_MainWindow.h"
const vector<string> MainWindow::operationStr = {"构造", "清空", "插入", "删除"};
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
  auto btnSiz = this->submitButton->size();
  this->submitButton->setGeometry(200, 200, btnSiz.width(), btnSiz.height());
  this->btree = nullptr;
  connect(this->operationMenu.get(), static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
    this, static_cast<void(MainWindow::*)(int)>(&MainWindow::operateBTree));
}

MainWindow::~MainWindow() {
  delete ui;
}

template<typename T>
void MainWindow::dumpBTree(const BTree<T>& btree) {
  btree.dumpToFile();
  this->pixmap->load("BTree.png");
  this->label->setPixmap(*(this->pixmap));
  this->subWindow->show();
}

void MainWindow::operateBTree(int op) {
  cout << "MainWindow::operateBTree(int op)" << endl;
  cout << op << ": " << this->operationStr[op] << endl;
}
