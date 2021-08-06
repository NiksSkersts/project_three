#include <modules/worldgen/map.h>
#include "AppInit.h"
using namespace std;
const constants c;
world_map worldMap(c);
AppInit::AppInit(int w, int h) {
    InitWindow(w,h,"project_two");
    SetTargetFPS(c.FPS);
    SetExitKey(27);
    //init noise settings;
    worldMap.noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    worldMap.noise.SetSeed(c.seed);
    worldMap.noise.SetFrequency(0.1);
    //end init;
    initCamera();
    gameLoop();
}
void AppInit::initCamera() {
    camera3D.position = {0,0,1000};
    camera3D.target = {0,0,0};
    camera3D.fovy = 180;
    camera3D.projection = CAMERA_ORTHOGRAPHIC;
    SetCameraMode(camera3D,CAMERA_FREE);
}
void AppInit::gameLoop() {
    while (!WindowShouldClose())
    {
        UpdateCamera(&camera3D);
        switch (GetKeyPressed()) {
            case KEY_UP:
                camera3D.position.y+=10;
                camera3D.target.y+=10;
                break;
            case KEY_DOWN:
                camera3D.position.y-=10;
                camera3D.target.y-=10;
                break;
            case KEY_RIGHT:
                camera3D.position.x+=10;
                camera3D.target.x+=10;
                break;
            case KEY_LEFT:
                camera3D.position.x-=10;
                camera3D.target.x-=10;
                break;
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
    BeginMode3D(camera3D);
    for (int i = 0; i < c.mapsize; ++i)
        for (int j = 0; j < c.mapsize; ++j)
            for (int k = 0; k < c.chunksize; ++k)
                for (int l = 0; l < c.chunksize; ++l) {
                    auto t = *worldMap.chunk_map.find(std::tuple(i*c.chunksize,j*c.chunksize))->second.tiles_in_chunk[k][l];
                    switch (t.type) {
                        case terrain_type::grass:
                            DrawCubeV({(t.coordinates.x*c.tilesize),(t.coordinates.y*c.tilesize),0},{(float)c.tilesize,(float )c.tilesize,1},GREEN);
                            break;
                            case terrain_type::water:
                                DrawCubeV({(t.coordinates.x*c.tilesize),(t.coordinates.y*c.tilesize),0},{(float)c.tilesize,(float )c.tilesize,1},BLUE);
                                break;
                                case terrain_type::hills:
                                    DrawCubeV({(t.coordinates.x*c.tilesize),(t.coordinates.y*c.tilesize),0},{(float)c.tilesize,(float )c.tilesize,1},RED);
                                    break;
                                    case terrain_type::forest:
                                        DrawRectangle(t.coordinates.x,t.coordinates.y,c.tilesize,c.tilesize,BLACK);
                                        break;
                    }
                }
    EndMode3D();
    DrawFPS(10, 10);
    EndDrawing();
}
