#include "AppInit.h"
using namespace std;
using namespace ui;
AppInit::AppInit()
// Opengl window init, map init and some basic config;
// Textures must be handled after OpenGL init!
{
    base_settings();
    init_camera();
    game_loop();
}
inline void AppInit::base_settings(){
    SetTargetFPS(var_fps);
    SetExitKey(27);
}
inline void AppInit::init_camera(){
    camera2D.target = {0,0};
    camera2D.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera2D.rotation = 0.0f;
    camera2D.zoom = 1.0f;
}
inline void AppInit::game_loop(){
    content::content_manager contentManager;
    auto world = worldgen::world_map(contentManager);
    while (!WindowShouldClose()){
        update(world);
        draw();
    }
#if DEBUG_MODE == false
    worldMap.function_sql_map(0);
#endif
    contentManager.function_unload_textures();
    CloseWindow();
}
void AppInit::update(worldgen::world_map &map)
//Update part of the loop. For variables, camera  updates and so on;
{
    //functions
    if (reload_map){
        function_add_chunks_to_queue(&map);
        reload_map = false;
    }
    reload_map = function_map_should_update();
    function_get_keypress();
}
void AppInit::function_add_chunks_to_queue(worldgen::world_map *map){
    int camera_x = (camera2D.target.x/1024)-1;
    int camera_y = (camera2D.target.y/1024)-1;
    //negative int will return SEGFAULT
    if(camera_x<0) camera_x = 0;
    if(camera_y<0) camera_y = 0;
    for (int i = 0; i < 3; ++i){
        std::array<worldgen::chunk *,3> row;
        std::array<worldgen::chunk_texture_map *,3> texture;
        for (int j = 0; j < 3; ++j)
        {
            auto chunk_id = worldgen::chunk::function_create_chunk_id(
                    (i+camera_x)*var_chunksize,
                    (j+camera_y)*var_chunksize);
            auto chk = map->chunk_and_texture_map.find(chunk_id);
            if (chk != map->chunk_and_texture_map.end()){
                row[j] = chk->second.first.get();
                texture[j] = chk->second.second.get();
            }else{
                row[j] = nullptr;
                texture[j] = nullptr;
            }
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

void AppInit::draw() {
    ClearBackground(BLACK);
    BeginDrawing();
    BeginMode2D(camera2D);
    for (unsigned long i = 0; i < map_temp_storage.size(); ++i) {
        for (unsigned long j = 0; j < map_temp_storage.size(); ++j) {
            if (map_temp_storage[i].second[j] == nullptr) break;
            for (int x = 0; x < var_chunksize; ++x) {
                for (int y = 0; y < var_chunksize; ++y) {
                    auto texture = map_temp_storage[i].second[j]->texture_map[x][y];
                    auto tile = map_temp_storage[i].first[j]->tiles_in_chunk[x][y].get();
                    auto obj = map_temp_storage[i].second[j]->object_map[x][y];
                    DrawTexture(
                            *texture,
                            tile->coordinates.x * tile->tilesize,
                            tile->coordinates.y * tile->tilesize,
                            WHITE
                    );
                    if (obj != nullptr && tile->type != worldgen::tile::terrain_type::border)
                        DrawTexture(*obj,
                                    tile->coordinates.x * tile->tilesize,
                                    tile->coordinates.y * tile->tilesize,
                                    WHITE
                        );
#if DEBUG_MODE
                    DrawText(to_string((int) tile->coordinates.x).append(to_string((int) tile->coordinates.y)).c_str(),
                             tile->coordinates.x * tile->tilesize,
                             tile->coordinates.y * tile->tilesize,
                             12,
                             WHITE
                    );
#endif
                }
            }
        }
    }
    EndMode2D();
    DrawFPS(10,10);
    EndDrawing();
}
