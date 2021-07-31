#include "main_menu.h"
#include "ui_main_menu.h"
#include "game_space.h"


main_menu::main_menu(QWidget *parent) :
        QWidget(parent), ui(new Ui::main_menu) {
    ui->setupUi(this);
    QObject::connect(ui->btn_play,&QPushButton::released,this,&main_menu::play_clicked);
    QObject::connect(ui->btn_quit,&QPushButton::released,this,&main_menu::exit_clicked);
}

main_menu::~main_menu() {
    delete ui;
}

void main_menu::play_clicked() {
    game_space *game_space_window = new game_space;
    game_space_window->resize(1000,1000);
    game_space_window->showMaximized();
    this->close();

}

void main_menu::exit_clicked() {
    exit(0);
}

