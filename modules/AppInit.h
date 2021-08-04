#include <raylib.h>
#include "map"
#include <basics/constants.h>
#include "raylib.h"

class AppInit {
private:
    void initCamera();
    void gameLoop();
    Camera2D camera2D;
    Camera3D camera3D;

public:
    AppInit(int w, int h);
private:
    void update();
    void draw();
};
