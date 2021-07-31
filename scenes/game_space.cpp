#include <world/tile.h>
#include <QExposeEvent>
#include "game_space.h"
#include "ui_game_space.h"


game_space::game_space(QWidget *parent) :
        QOpenGLWidget(parent), ui(new Ui::game_space) {
    this->setMinimumHeight(400);
    this->setMinimumWidth(400);
    ui->setupUi(this);
}

game_space::~game_space() {
    delete ui;
}

