//
// Created by niks-skersts on 7/31/21.
//

#ifndef PROJECT_TWO_MAIN_MENU_H
#define PROJECT_TWO_MAIN_MENU_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class main_menu; }
QT_END_NAMESPACE

class main_menu : public QWidget {
Q_OBJECT

public:
    explicit main_menu(QWidget *parent = nullptr);

    ~main_menu() override;

private:
    Ui::main_menu *ui;
};


#endif //PROJECT_TWO_MAIN_MENU_H
