#include "AppInit.h"
#include "queue"
#include <future>
using namespace std;
const constants c;
world_map worldMap(c);
vector<chunk> map_queue;
AppInit::AppInit()
//Opengl window init, map init and some basic config;
{
    width = GetScreenWidth()/2;
    height = GetScreenHeight()/2;
    //fallback values
    if (width == 0) width = 500;
    if (height == 0) height = 500;
    InitWindow(width,height,"project_two");
    function_load_textures();
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
void AppInit::initCamera()
//Camera init
{
    camera2D.target = { GetScreenWidth() + 20.0f, GetScreenHeight() + 20.0f };
    camera2D.offset = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    camera2D.rotation = 0.0f;
    camera2D.zoom = 2.0f;
    camera3D.position = {0,0,50};
    camera3D.target = {0,0,0};
    camera3D.fovy = 180;
    camera3D.projection = CAMERA_ORTHOGRAPHIC;
    SetCameraMode(camera3D,CAMERA_FREE);
}
void AppInit::gameLoop()
//Base gameloop and de-init when the while loop breaks;
{
    while (!WindowShouldClose())
    {
        update();
        draw();
    }
    //de-init part
    UnloadTexture(grass_texture);
    UnloadTexture(water_texture);
    UnloadTexture(button_build_texture);
    UnloadTexture(mountain_texture);
    CloseWindow();
}
void AppInit::update()
//Update part of the loop. For variable, camera  updates and so on;
{
    //update window size for responsive layout;
    height = GetScreenHeight();
    width = GetScreenWidth();
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
}
void AppInit::draw()
//Draw part of the loop. Rendering part
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
    //overlay
    DrawTexture(button_build_texture,10,height-(c.tilesize+10), Fade(WHITE,1.0f));
    DrawFPS(10, 10);
    //functions
    if (IsKeyDown(KEY_A))
    {
        auto i = std::async(std::launch::deferred,&AppInit::function_get_current_obj,this);
        DrawText(i.get(),10,40,40,WHITE);
    }
    EndDrawing();
}
void AppInit::function_load_textures()
//Load textures on app init;
{
    //images
    grass = LoadImage("../assets/png/grass2.png");
    water = LoadImage("../assets/png/water.png");
    mountain = LoadImage("../assets/png/mountain.png");
    //button_images
    button_build_img = LoadImage("../assets/png/button_build.png");
    //textures
    grass_texture = LoadTextureFromImage(grass);
    water_texture = LoadTextureFromImage(water);
    mountain_texture = LoadTextureFromImage(mountain);
    //button_textures
    button_build_texture = LoadTextureFromImage(button_build_img);
    //unload - img no longer needed;
    UnloadImage(grass);
    UnloadImage(water);
    UnloadImage(mountain);
    UnloadImage(button_build_img);
}
void AppInit::function_add_chunks_to_queue()
//load chunks into a vector;
//Vector will be used to limit the amount of loaded chunks;
{
        for (int i = 0; i < c.mapsize; ++i)
            for (int j = 0; j < c.mapsize; ++j){
                auto b = worldMap.chunk_map.find(std::tuple(i*c.chunksize,j*c.chunksize));
                auto t = *&b->second;
                map_queue.push_back(t);
            }
}
const char * AppInit::function_get_current_obj()
//Gets current tile based on ScreenToWorld coords and return the object that's on tile;
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
                        return "hill";
                        case object_type::Forest:
                            return "forest";
                }
            }
        return "No objects found";
}
