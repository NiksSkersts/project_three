#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

class main_screen : public QMainWindow
    {
  Q_OBJECT

  int32_t mButtonPressedAmt;

  QLabel* mpLabel;
  QPushButton* mpPushButton;

  void updateLabelText();

    public:
      main_screen(QWidget* parent = nullptr);
      ~main_screen() = default;

      signals:
      void sigLabelTextUpdated(std::string_view);
    };