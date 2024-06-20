#ifndef PASSWORD_GENERATOR_QT__COLORED_PROGRESSBAR_H_
#define PASSWORD_GENERATOR_QT__COLORED_PROGRESSBAR_H_

#include <QWidget>
#include <QProgressBar>
#include <QPaintEvent>

class ColoredProgressBar : public QProgressBar {
 Q_OBJECT
 public:
  explicit ColoredProgressBar(QWidget *parent = 0);

 protected:
  void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

};

#endif //PASSWORD_GENERATOR_QT__COLORED_PROGRESSBAR_H_
