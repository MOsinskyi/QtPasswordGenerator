#include "../headers/main-window.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  auto *window = new MainWindow;
  window->setWindowIcon(QIcon("img/icon.ico"));
  window->show();
  return QApplication::exec();
}
