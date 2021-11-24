#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <memory>
#include <vector>
#include <string>
#include "BTree.hh"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
using std::unique_ptr;
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  template<typename T> void dumpBTree(BTree<T>* btree);
  void operateBTree(int op);
  void procInput(int op, const string& str);

private:
  Ui::MainWindow* ui;
  unique_ptr<QMainWindow> subWindow;
  unique_ptr<QLabel> label;
  unique_ptr<QPixmap> pixmap;
  unique_ptr<QComboBox> operationMenu;
  unique_ptr<QPushButton> submitButton;
  unique_ptr<BTree<int>> btree;
  unique_ptr<QTextEdit> input;
  static const vector<string> operationStr;

protected:
  // virtual void mousePressEvent(QMouseEvent* event);
};
#endif // MAINWINDOW_H
