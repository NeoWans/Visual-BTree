#include "MainWindow.h"

#include <QApplication>

signed main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
