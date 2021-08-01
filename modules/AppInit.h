//
// Created by niks-skersts on 8/1/21.
//

#ifndef PROJECT_TWO_APPINIT_H
#define PROJECT_TWO_APPINIT_H


#include <raylib.h>

class AppInit {
public:
    AppInit(int w, int h);
    void initCamera();
    void gameLoop();
public:
    Camera2D camera;
    bool req_close = false;


    void update();

    void draw();

    void initMap();
};


#endif //PROJECT_TWO_APPINIT_H
