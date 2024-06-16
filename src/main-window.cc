#include "../main-window.h"
#include <QtWidgets>

enum PasswordLength {
  MIN = 8,
  MAX = 30
};

const QString kOptions[] = {
    "QWERTYUIOPASDFGHJKLZXCVBNM",
    "qwertyuiopasdfghjklzxcvbnm",
    "0123456789",
    "-----",
    "_____",
    "     ",
    "!@#$%^&*:;?.,~`/",
    "(){}[]<>"
};

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent) {
  InitUserInterface();

  connect(create_password_, &QPushButton::clicked, this,
          &MainWindow::GeneratePassword);
  connect(copy_password_btn_, &QPushButton::clicked, this, &MainWindow::CopyPassword);

  ConfigureLayout();

  setFixedSize(QDialog::sizeHint().width(), QDialog::sizeHint().height());
}

void MainWindow::ConfigureLayout() {
  auto *password_length_layout = new QHBoxLayout;
  password_length_layout->addWidget(length_password_lbl_);
  password_length_layout->addWidget(length_password_spin_box_);

  auto *first_column_check_boxes = new QVBoxLayout;
  for (int i = 0; i < 4; ++i) {
    first_column_check_boxes->addWidget(check_boxes_[i]);
  }

  auto *second_column_check_boxes = new QVBoxLayout;
  for (int i = 4; i < 8; ++i) {
    second_column_check_boxes->addWidget(check_boxes_[i]);
  }
  second_column_check_boxes->addStretch();

  auto *checkboxes = new QHBoxLayout;
  checkboxes->addLayout(first_column_check_boxes);
  checkboxes->addLayout(second_column_check_boxes);

  auto *main_layout = new QVBoxLayout;
  main_layout->addLayout(password_length_layout);
  main_layout->addLayout(checkboxes);
  main_layout->addWidget(create_password_);
  main_layout->addWidget(generated_password_lbl_);
  main_layout->addWidget(generated_password_field_);
  main_layout->addWidget(password_strength_);
  main_layout->addWidget(copy_password_btn_);
  setLayout(main_layout);
}

void MainWindow::InitUserInterface() {
  length_password_lbl_ = new QLabel("Enter password length: ");

  length_password_spin_box_ = new QSpinBox;
  length_password_spin_box_->setRange(MIN, MAX);

  length_password_lbl_->setBuddy(length_password_spin_box_);

  const QString kLabels[] = {
      "Upper-case (A, B, C, ...)",
      "Lower-case (a, b, c, ...)",
      "Digits (0, 1, 2, ...)",
      "Minus (-)",
      "Underline (_)",
      "Space ( )",
      "Special (!, $, %, &, ...)",
      "Brackets ([, ], {, }, (, ), <, >)"
  };

  for (int i = 0; i < 8; ++i) {
    check_boxes_[i] = new QCheckBox(kLabels[i]);
    check_boxes_[i]->setCheckState((i < 2) ? Qt::Checked : Qt::Unchecked);
  }

  create_password_ = new QPushButton("Generate password");

  generated_password_lbl_ = new QLabel("Your generated password: ");
  generated_password_field_ = new QLineEdit;
  generated_password_field_->setReadOnly(true);

  password_strength_ = new QProgressBar;
  password_strength_->setAlignment(Qt::AlignCenter);

  copy_password_btn_ = new QPushButton("Copy password");
}

void MainWindow::GeneratePassword() {
  QString possible_characters;

  for (int i = 0; i < 8; ++i) {
    if (check_boxes_[i]->isChecked()) {
      possible_characters += kOptions[i];
    }
  }

  if (possible_characters.isEmpty()) {
    generated_password_field_->setText("Select at least one character set!");
    return;
  }

  int password_length = length_password_spin_box_->value();
  QString password;

  for (int i = 0; i < password_length; ++i) {
    auto random_index = QRandomGenerator::global()->bounded(possible_characters.length());
    password += possible_characters[random_index];
  }

  generated_password_field_->setText(password);
  copy_password_btn_->setText("Copy password");
  SetPasswordStrength(password);

}

void MainWindow::CopyPassword() {
  generated_password_field_->selectAll();
  generated_password_field_->copy();
  copy_password_btn_->setText("Password copied to clipboard!");
}

void MainWindow::SetPasswordStrength(const QString &password) {
  auto length = password.length();
  bool has_upper_case = password.contains(QRegularExpression("[A-Z]"));
  bool has_lower_case = password.contains(QRegularExpression("[a-z]"));
  bool has_digits = password.contains(QRegularExpression("[0-9]"));
  bool has_special = password
      .contains(QRegularExpression(R"([!@#$%^&*:;/?.,~`\-\_\[\]\{\}\(\)\<\> ])"));
  bool has_space = password.contains(" ");

  int strength = (int) length * 2;

  if (has_upper_case) strength += 2;
  if (has_lower_case) strength += 3;
  if (has_digits) strength += 5;
  if (has_special) strength += 20;
  if (has_space) strength += 10;

  password_strength_->setValue(strength);
}
