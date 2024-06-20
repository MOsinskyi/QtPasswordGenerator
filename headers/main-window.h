#ifndef PASSWORD_GENERATOR_QT__MAIN_WINDOW_H_
#define PASSWORD_GENERATOR_QT__MAIN_WINDOW_H_

#include <QDialog>
#include "colored-progressbar.h"

class QLabel;
class QSpinBox;
class QCheckBox;
class QLineEdit;
class QPushButton;
class ColoredProgressBar;

class MainWindow : public QDialog {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);

 private slots:
  void GeneratePassword();
  void CopyPassword();

 private:
  QLabel *length_password_lbl_;
  QSpinBox *length_password_spin_box_;

  QCheckBox *check_boxes_[8];

  QPushButton *create_password_;

  QLabel *generated_password_lbl_;
  QLineEdit *generated_password_field_;

  ColoredProgressBar *password_strength_;

  QPushButton *copy_password_btn_;

  void InitUserInterface();
  void ConfigureLayout();
  void SetPasswordStrength(const QString &password);
};

#endif
