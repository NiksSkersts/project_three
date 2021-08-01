//
// Created by niks-skersts on 8/1/21.
//

#include <tuple>
#include <map>
#include <modules/worldgen/chunk.h>
#include <basics/constants.h>
#include <modules/worldgen/terrain_type.h>
#include <vector>
#include "AppInit.h"
#include "raylib.h"
Vector3 cubePosition;
constants c;
std::map<std::tuple<float,float>,chunk> arr;
AppInit::AppInit(int w, int h) {
    InitWindow(w,h,"project_two");
    SetTargetFPS(c.FPS);               // Set our game to run at 60 frames-per-second
    initCamera();
    cubePosition = { 0.0f, 0.0f, 0.0f };
    gameLoop();
}
void AppInit::initMap()
{
}
void AppInit::initCamera() {
    camera.offset = (Vector2){0,0};
    camera.target = (Vector2){ 0.0f, 0.0f };      // Camera looking at point
    camera.zoom= 1;
}

void AppInit::gameLoop() {
    while (!req_close==true)
    {
        update();
        draw();
    }
    CloseWindow();
}
void AppInit::update()
{
    if (arr.count()>9)
        arr.clear();
    arr.emplace(std::tuple(0,0),chunk((Vector2){0,0}));
}
void AppInit::draw()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    BeginMode2D(camera);
    for (auto x:arr) {
        for (auto y:x.second.chunk_array) {
            if (y.second.type==terrain_type::grass)
                DrawRectangleLines(y.second.coordinates.x+(31*y.second.coordinates.x),(y.second.coordinates.y*31)+y.second.coordinates.y,32,32,GREEN);
            if (y.second.type==terrain_type::hills)
                DrawRectangleLines(y.second.coordinates.x+(31*y.second.coordinates.x),(y.second.coordinates.y*31)+y.second.coordinates.y,32,32,GRAY);
            if (y.second.type==terrain_type::water)
                DrawRectangleLines(y.second.coordinates.x+(31*y.second.coordinates.x),(y.second.coordinates.y*31)+y.second.coordinates.y,32,32,BLUE);
        }
    }
    EndMode3D();
    DrawFPS(10, 10);
    EndDrawing();
}

