#include "AppInit.h"
#include "queue"
using namespace std;
const constants c;
world_map worldMap(c);
vector<chunk> map_queue;
AppInit::AppInit(int w, int h) {
    InitWindow(w,h,"project_two");
    LoadTextures();
    SetTargetFPS(c.FPS);
    SetExitKey(27);
    //init noise settings;
    worldMap.noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    worldMap.noise.SetSeed(c.seed);
    //end init;
    function_add_chunks_to_queue();
    initCamera();
    gameLoop();
}
void AppInit::initCamera() {
    camera2D.target = { GetScreenWidth() + 20.0f, GetScreenHeight() + 20.0f };
    camera2D.offset = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    camera2D.rotation = 0.0f;
    camera2D.zoom = 1.0f;
    camera3D.position = {0,0,50};
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
                camera2D.target.y-=100;
                break;
            case KEY_DOWN:
                camera2D.target.y+=100;
                break;
            case KEY_RIGHT:
                camera2D.target.x+=100;
                break;
            case KEY_LEFT:
                camera2D.target.x-=100;
                break;
        }
        update();
        draw();
    }
    UnloadTexture(grass_texture);
    UnloadTexture(water_texture);
    CloseWindow();
}
void AppInit::update()
{
}
void AppInit::draw()
{
    ClearBackground(BLACK);
    BeginDrawing();
    BeginMode2D(camera2D);
    for (auto chk : map_queue)
        for (int i = 0; i < c.chunksize; ++i)
            for (int j = 0; j < c.chunksize; ++j) {
                auto t = *chk.tiles_in_chunk[i][j];
                switch (t.type) {
                    case terrain_type::grass:
                        DrawTexture(grass_texture,(t.coordinates.x*c.tilesize),(t.coordinates.y*c.tilesize),Fade(WHITE,1.0f));
                        break;
                        case terrain_type::water:
                            DrawTexture(water_texture,(t.coordinates.x*c.tilesize),(t.coordinates.y*c.tilesize),Fade(WHITE,1.0f));
                            break;
                            case terrain_type::hills:
                                DrawTexture(grass_texture,(t.coordinates.x*c.tilesize),(t.coordinates.y*c.tilesize),Fade(WHITE,1.0f));
                                break;
                                case terrain_type::forest:
                                    DrawTexture(water_texture,(t.coordinates.x*c.tilesize),(t.coordinates.y*c.tilesize),Fade(WHITE,1.0f));
                                    break;
                }
                switch (t.obj) {
                    case object_type::NONE:
                        break;
                    case object_type::Forest:
                        break;
                    case object_type::Hill:
                        DrawTexture(mountain_texture,(t.coordinates.x*c.tilesize),(t.coordinates.y*c.tilesize),Fade(WHITE,1.0f));
                        break;
                }
            }

    EndMode2D();
    function_get_current_obj();
    DrawFPS(10, 10);
    EndDrawing();
}
void AppInit::LoadTextures()
{
    grass = LoadImage("../assets/png/grass2.png");
    water = LoadImage("../assets/png/water.png");
    mountain = LoadImage("../assets/png/mountain.png");
    grass_texture = LoadTextureFromImage(grass);
    water_texture = LoadTextureFromImage(water);
    mountain_texture = LoadTextureFromImage(mountain);
    //unload - img no longer needed;
    UnloadImage(grass);
    UnloadImage(water);
}
void AppInit::function_add_chunks_to_queue()
{
    for (int i = 0; i < c.mapsize; ++i)
        for (int j = 0; j < c.mapsize; ++j){
                    auto b = worldMap.chunk_map.find(std::tuple(i*c.chunksize,j*c.chunksize));
                    auto t = *&b->second;
                    map_queue.push_back(t);
                }
}
void AppInit::function_get_current_obj() {
    if (IsKeyDown(KEY_A))
    {
        auto stw= GetScreenToWorld2D(GetMousePosition(),camera2D);
        auto chunk_x =(int) (stw.x/((c.chunksize*c.chunksize)));
        auto chunk_y =(int) (stw.y/(c.chunksize*c.chunksize));
        auto coord_x = ((int)(stw.x/c.chunksize));
        auto coord_y = ((int)(stw.y/c.chunksize));
        if (chunk_x>0) coord_x= coord_x - (c.chunksize*chunk_x);
        if (chunk_y>0) coord_y = coord_y - (c.chunksize*chunk_x);
        for (auto chk : map_queue)
            if (chk.starting_coordinates.x == (float)chunk_x*c.chunksize && chk.starting_coordinates.y == (float)chunk_y*c.chunksize)
            {
                auto z =*chk.tiles_in_chunk[coord_x][coord_y];
                switch (z.obj) {
                    case object_type::NONE:
                        break;
                    case object_type::Hill:
                        DrawText("hill",10,40,20,BLACK);
                        break;
                        case object_type::Forest:
                            DrawText("forest",10,40,20,BLACK);
                            break;
                }
            }

        }
}
