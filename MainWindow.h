#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QPainter>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
using std::unique_ptr;
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow* ui;
  unique_ptr<QLabel> label;
  unique_ptr<QPixmap> pixmap;
  unique_ptr<QPainter> painter;
};
#endif // MAINWINDOW_H
