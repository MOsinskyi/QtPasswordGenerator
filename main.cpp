#include "main-window.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  auto *window = new MainWindow;
  window->show();
  return QApplication::exec();
}
