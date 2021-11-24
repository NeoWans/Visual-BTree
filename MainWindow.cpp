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
  this->btree = nullptr;
  this->input = unique_ptr<QTextEdit>(new QTextEdit(this));
  this->input->setText("");
  connect(this->submitButton.get(), &QPushButton::clicked, this, [&]() {
    procInput(this->operationMenu->currentIndex(), (this->input->toPlainText()).toStdString());
    dumpBTree(this->btree.get());
    });
  this->input->setGeometry(0, 0, 600, 600);
  this->operationMenu->setGeometry(600, 0, 200, 100);
  this->submitButton->setGeometry(600, 100, 200, 100);
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
  cout << "MainWindow::procInput(int op, const string& str)" << endl;
  cout << op << " " << str << endl;
}

void MainWindow::operateBTree(int op) {
  cout << "MainWindow::operateBTree(int op)" << endl;
  cout << op << ": " << this->operationStr[op] << endl;
}
