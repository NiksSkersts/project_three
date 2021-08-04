#include <modules/worldgen/map.h>
#include "AppInit.h"
using namespace std;
const constants c;
world_map worldMap(c);
AppInit::AppInit(int w, int h) {
    InitWindow(w,h,"project_two");
    SetTargetFPS(c.FPS);
    SetExitKey(27);
    initCamera();
    gameLoop();
}
void AppInit::initCamera() {
    camera2D.zoom = 1.0f;
    camera2D.offset = {GetScreenWidth()+0.0f,GetScreenHeight()+0.0f};
    camera2D.target = {0.0f,0.0f};
    camera3D.position = {0,0,500};
    camera3D.target = {21,21,0};
    camera3D.fovy = 120;
    camera3D.projection = CAMERA_ORTHOGRAPHIC;
    SetCameraMode(camera3D,CAMERA_FREE);
}
void AppInit::gameLoop() {
    while (!WindowShouldClose())
    {
        UpdateCamera(&camera3D);
        switch (GetKeyPressed()) {
            case KEY_UP:
                camera3D.target.y+=10;
                camera3D.position.y+=10;
                break;
            case KEY_DOWN:
                camera3D.target.y-=10;
                camera3D.position.y-=10;
                break;
            case KEY_RIGHT:
                camera3D.target.x+=10;
                camera3D.position.x+=10;
                break;
            case KEY_LEFT:
                camera3D.target.x-=10;
                camera3D.position.x-=10;
                break;
            case KEY_W:
                camera3D.target.z+=100;
                break;
            case KEY_S:
                camera3D.target.z-=100;
        }
        update();
        draw();
    }
    CloseWindow();
}
void AppInit::update()
{
}
void AppInit::draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
        //BeginMode2D(camera2D);
        BeginMode3D(camera3D);
        for (auto x:worldMap.chunk_map)
            for(auto y : x.second.tiles_in_chunk)
            {
                switch (y.type) {
                    case terrain_type::grass:
                        DrawCubeV({(y.coordinates.x*c.tilesize),(y.coordinates.y*c.tilesize),0},{(float)c.tilesize,(float )c.tilesize,1},GREEN);
                        break;
                        case terrain_type::water:
                            DrawCubeV({(y.coordinates.x*c.tilesize),(y.coordinates.y*c.tilesize),0},{(float)c.tilesize,(float )c.tilesize,1},BLUE);
                            break;
                            case terrain_type::hills:
                                DrawCubeV({(y.coordinates.x*c.tilesize),(y.coordinates.y*c.tilesize),0},{(float)c.tilesize,(float )c.tilesize,1},GRAY);
                                break;
                                case terrain_type::forest:
                                    DrawRectangle(y.coordinates.x,y.coordinates.y,c.tilesize,c.tilesize,BLACK);
                                    break;
                }
            }
        //EndMode2D();
        EndMode3D();
    DrawFPS(10, 10);
    EndDrawing();
}
