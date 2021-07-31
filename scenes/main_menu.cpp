//
// Created by niks-skersts on 7/31/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_menu.h" resolved

#include "main_menu.h"
#include "ui_main_menu.h"


main_menu::main_menu(QWidget *parent) :
        QWidget(parent), ui(new Ui::main_menu) {
    ui->setupUi(this);
}

main_menu::~main_menu() {
    delete ui;
}

