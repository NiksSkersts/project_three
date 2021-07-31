//
// Created by niks-skersts on 7/31/21.
//

#ifndef PROJECT_TWO_MAIN_MENU_H
#define PROJECT_TWO_MAIN_MENU_H

#include <QWidget>
#include <QPushButton>


QT_BEGIN_NAMESPACE
namespace Ui { class main_menu; }
QT_END_NAMESPACE

class main_menu : public QWidget {
Q_OBJECT
public:
    QPushButton btn_play;
    QPushButton btn_settings;
    QPushButton btn_quit;
    explicit main_menu(QWidget *parent = nullptr);
    ~main_menu() override;

private:
Ui::main_menu *ui;
public slots:
    void play_clicked();
    void exit_clicked();
};


#endif //PROJECT_TWO_MAIN_MENU_H
