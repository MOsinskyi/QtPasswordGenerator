#include "../headers/colored-progressbar.h"

#include <QPainter>
#include <QBrush>
#include <QStyle>
#include <QColor>

void ColoredProgressBar::paintEvent(QPaintEvent *) {
  int val = value() + 1;
  int w = width();
  int h = height();
  int pos = QStyle::sliderPositionFromValue(minimum(), maximum(), val, width());

  QPixmap pixmap(w, h);
  QPainter pixmap_painter(&pixmap);
  QLinearGradient linear_gradient(0, 0, w, h);
  linear_gradient.setColorAt(0, Qt::red);
  linear_gradient.setColorAt(0.5, Qt::yellow);
  linear_gradient.setColorAt(1, Qt::green);

  QBrush pixmap_brush(linear_gradient);
  pixmap_painter.setBrush(pixmap_brush);
  pixmap_painter.drawRect(0, 0, width(), height());

  QPainter painter(this);
  QBrush brush(pixmap);
  painter.setBrush(brush);
  painter.drawRect(0, 0, pos, height());

  painter.setPen(Qt::lightGray);
  painter.setBrush(QBrush(Qt::lightGray));
  painter.drawRect(pos, 0, width(), height());

  painter.setPen(Qt::black);
  painter.setBrush(QBrush(Qt::black));
  painter.drawText(0, 0, width(), height(), Qt::AlignCenter, QString::number(val) + " bits");
}

ColoredProgressBar::ColoredProgressBar(QWidget *parent) : QProgressBar(parent) {

}
