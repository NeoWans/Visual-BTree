#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QComboBox>
#include <QPushButton>
#include <memory>
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
  template<typename T> void dumpBTree(const BTree<T>& tr);

private:
  Ui::MainWindow* ui;
  unique_ptr<QMainWindow> subWindow;
  unique_ptr<QLabel> label;
  unique_ptr<QPixmap> pixmap;
  unique_ptr<QComboBox> operationMenu;
  unique_ptr<QPushButton> submitButton;

protected:
  // virtual void mousePressEvent(QMouseEvent* event);
};
#endif // MAINWINDOW_H
