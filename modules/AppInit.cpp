#include "AppInit.h"
using namespace std;
using namespace main_logic;
AppInit::AppInit()
// Opengl window init, map init and some basic config;
// Textures must be handled after OpenGL init!
{
    InitWindow(width, height, "project_two");
    base_settings();
    init_camera();
    game_loop();
}
inline void AppInit::base_settings(){
    SetTargetFPS(var_fps);
    SetExitKey(27);
}
inline void AppInit::init_camera()
// Camera init
{
    camera2D.target = {0,0};
    camera2D.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera2D.rotation = 0.0f;
    camera2D.zoom = 1.0f;
}
inline void AppInit::game_loop()
// Base gameloop and de-init when the while loop breaks;
{
    content::content_manager contentManager;
    auto world = worldgen::world_map(contentManager);
    while (!WindowShouldClose()){
        update(world);
        draw();
    }
    //disabled to speed up debug
    //worldMap.function_sql_map(0);
    contentManager.function_unload_textures();
    CloseWindow();
}
void AppInit::update(worldgen::world_map &map)
// Update part of the loop. For variables, camera  updates and so on;
{
    //update variables
    width = GetScreenWidth();
    height = GetScreenHeight();
    //functions
    if (reload_map){
        function_add_chunks_to_queue(map);
        reload_map = false;
    }
    reload_map = function_map_should_update();
    function_get_keypress();
}
void AppInit::function_add_chunks_to_queue(worldgen::world_map &map)
// load chunks into a vector;
// Vector will be used to limit the amount of loaded chunks;
{
    auto camera_x = (int)(camera2D.target.x/1024)-1;
    auto camera_y = (int)(camera2D.target.y/1024)-1;
    auto camera_x_end = camera_x+3;
    auto camera_y_end = camera_y+3;
    //negative int will return SEGFAULT
    if(camera_x<0) camera_x = 0;
    if(camera_y<0) camera_y = 0;
    if(camera_x_end>var_mapsize) camera_x_end = var_mapsize;
    if (camera_y_end>var_mapsize)camera_y_end = var_mapsize;
    for (int i = 0; i < 3; ++i){
        std::array<worldgen::chunk *,3> row;
        std::array<worldgen::chunk_texture_map *,3> texture;
        for (int j = 0; j < 3; ++j)
        {
            auto b = map.chunk_and_texture_map.find(worldgen::chunk::function_create_chunk_id((i) * var_chunksize, (j) * var_chunksize));
            row[j] = b->second.first.get();
            texture[j] = b->second.second.get();
        }
        map_temp_storage[i].first = row;
        map_temp_storage[i].second = texture;
    }
}
bool AppInit::function_map_should_update(){
    if(camera2D.target.x>old_coordinates.x+var_upd_range ||
            camera2D.target.x<old_coordinates.x-var_upd_range ||
            camera2D.target.y>old_coordinates.y+var_upd_range ||
            camera2D.target.y<old_coordinates.y-var_upd_range
            ){
        old_coordinates = camera2D.target;
        return true;
    }
    //todo fix this
    return false;
}
void AppInit::function_get_keypress(){
    switch (GetKeyPressed())
    {
        case KEY_UP:
            camera2D.target.y -= 100;
            break;
        case KEY_DOWN:
            camera2D.target.y += 100;
            break;
        case KEY_RIGHT:
            camera2D.target.x += 100;
            break;
        case KEY_LEFT:
            camera2D.target.x -= 100;
            break;
        case MOUSE_LEFT_BUTTON:
            break;
    }

}
void AppInit::draw()
{
    ClearBackground(BLACK);
    BeginDrawing();
    BeginMode2D(camera2D);
    for (unsigned long i = 0; i < map_temp_storage.size();++i) {
        for (unsigned long j = 0; j < map_temp_storage.size();++j) {
            for (int x =0;x<var_chunksize;++x) {
                for (int y = 0; y < var_chunksize; ++y) {
                    auto texture = map_temp_storage[i].second[j]->texture_map[x][y];
                    auto tile = map_temp_storage[i].first[j]->tiles_in_chunk[x][y].get();
                    auto obj = map_temp_storage[i].second[j]->object_map[x][y];
                    DrawTexture(*texture,tile->coordinates.x*tile->tilesize,tile->coordinates.y*tile->tilesize,WHITE);
                    if(obj!= nullptr && tile->type!=worldgen::tile::terrain_type::border)
                        DrawTexture(*obj,tile->coordinates.x*tile->tilesize,tile->coordinates.y*tile->tilesize,WHITE);
                    DrawText(to_string((int)tile->coordinates.x).append(to_string((int)tile->coordinates.y)).c_str(),tile->coordinates.x*tile->tilesize,tile->coordinates.y*tile->tilesize,12,WHITE);
                }
            }
        }
    }
    EndMode2D();
    EndDrawing();
}
