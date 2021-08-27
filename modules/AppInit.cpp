#include "AppInit.h"
using namespace std;
using namespace main_logic;
worldgen::world_map worldMap;
vector<worldgen::chunk> map_queue;
ui::game_ui gm;
bool reload_map {true};
Vector2 old_coordinates{0,0};
int var_upd_range{100};
constexpr int var_chunksize {worldgen::chunk::var_chunksize};
constexpr int var_mapsize {worldgen::world_map::var_mapsize};
constexpr int var_fps {240};
AppInit::AppInit()
// Opengl window init, map init and some basic config;
// Textures must be handled after OpenGL init!
{
    width = GetScreenWidth() / 2;
    height = GetScreenHeight() / 2;
    // fallback values
    if (width == 0)
        width = 1500;
    if (height == 0)
        height = 1000;
    InitWindow(width, height, "project_two");
    content::content_manager cm;
    initCamera();
    gameLoop(cm);
}
void AppInit::initCamera()
// Camera init
{
    camera2D.target = {0,0};
    camera2D.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera2D.rotation = 0.0f;
    camera2D.zoom = 5.0f;
}
void AppInit::gameLoop(content::content_manager &manager)
// Base gameloop and de-init when the while loop breaks;
{
    map_queue.reserve(16);
    SetTargetFPS(var_fps);
    SetExitKey(27);
    while (!WindowShouldClose()){
        update();
        draw(manager);
    }
    // de-init part
    //disabled to speed up debug
    //worldMap.function_sql_map(0);
    manager.function_unload_textures();
    CloseWindow();
}
void AppInit::update()
// Update part of the loop. For variables, camera  updates and so on;
{
    //variables
    height = GetScreenHeight();
    width = GetScreenWidth();
    reload_map = function_map_should_update();
    //functions
    if (reload_map){
        function_add_chunks_to_queue();
        reload_map = false;
    }
    function_get_keypress();
}
void AppInit::function_add_chunks_to_queue()
// load chunks into a vector;
// Vector will be used to limit the amount of loaded chunks;
{
    map_queue.clear();
    auto camera_x = (int)(camera2D.target.x/1024)-1;
    auto camera_y = (int)(camera2D.target.y/1024)-1;
    auto camera_x_end = camera_x+3;
    auto camera_y_end = camera_y+3;
    //negative int will return SEGFAULT
    if(camera_x<0) camera_x = 0;
    if(camera_y<0) camera_y = 0;
    if(camera_x_end>var_mapsize) camera_x_end = var_mapsize;
    if (camera_y_end>var_mapsize)camera_y_end =var_mapsize;

    for (int i = (int)camera_x; i < camera_x_end; ++i)
        for (int j = (int)camera_y; j < camera_y_end; ++j)
        {
            auto b = worldMap.chunk_map.find(std::tuple(i * var_chunksize, j * var_chunksize));
            auto t = *&b->second;
            map_queue.push_back(t);
        }
}
bool AppInit::function_map_should_update(){
    if(old_coordinates.x == 0 && old_coordinates.y == 0 && map_queue.empty()){
        return true;
    }
    if(camera2D.target.x>old_coordinates.x+var_upd_range ||
            camera2D.target.x<old_coordinates.x-var_upd_range ||
            camera2D.target.y>old_coordinates.y+var_upd_range ||
            camera2D.target.y<old_coordinates.y-var_upd_range){
        old_coordinates = camera2D.target;
        return true;
    }
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
            uint in_button_border = function_check_button_boundaries();
            if (in_button_border !=0){
                cout<<"here";
            };
            break;
    }

}
void AppInit::draw(content::content_manager manager)
// Draw part of the loop. Rendering part
{
    ClearBackground(BLACK);
    BeginDrawing();
    BeginMode2D(camera2D);
    for (auto chk : map_queue)
        for (int x =0;x<var_chunksize;++x)
            for(int y =0;y<var_chunksize;++y){
                auto t = chk.tiles_in_chunk[x][y];
                switch (t.type) {
                    case worldgen::terrain_type::grass:
                        DrawTextureRec(manager.grass_texture,{0,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        DrawTextureRec(manager.grass_texture,{32,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        DrawTextureRec(manager.grass_texture,{64,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        DrawTextureRec(manager.grass_texture,{96,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        DrawTextureRec(manager.grass_texture,{128,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        DrawTextureRec(manager.grass_texture,{160,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        DrawTextureRec(manager.grass_texture,{192,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        DrawTextureRec(manager.grass_texture,{224,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        DrawTextureRec(manager.grass_texture,{256,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        break;
                    case worldgen::terrain_type::water:
                        DrawTextureRec(manager.water_texture,{0,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        DrawTextureRec(manager.water_texture,{32,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        DrawTextureRec(manager.water_texture,{64,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        DrawTextureRec(manager.water_texture,{96,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        DrawTextureRec(manager.water_texture,{128,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        DrawTextureRec(manager.water_texture,{160,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        DrawTextureRec(manager.water_texture,{192,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        DrawTextureRec(manager.water_texture,{224,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        DrawTextureRec(manager.water_texture,{256,0,32,32},{t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize},WHITE);
                        break;
                    case worldgen::terrain_type::hills:
                        DrawTexture(manager.mountain_texture,t.coordinates.x*t.tilesize,t.coordinates.y*t.tilesize,WHITE);
                        break;
                    case worldgen::terrain_type::forest:
                        break;
                }
            }
    EndMode2D();
    // functions
    function_draw_ui(manager);
    EndDrawing();
}
void AppInit::function_draw_map(content::content_manager manager,worldgen::tile tile){
    for(int x = tile.coordinates.x-1;x<tile.coordinates.x+2;++x){
        for(int y = tile.coordinates.x-1;y<tile.coordinates.y+2;++y){
            //auto ch_comp = map_queue.find(std::tuple((int)var_chunksize*(x/var_chunksize),(int)var_chunksize*(y/var_chunksize)));
        }
    }
}
const char *AppInit::function_get_current_obj()
// Gets current tile based on ScreenToWorld coords and return the object that's
// on tile;
{
    auto stw = GetScreenToWorld2D(GetMousePosition(), camera2D);
    auto chunk_x = (int)(stw.x / ((var_chunksize * var_chunksize)));
    auto chunk_y = (int)(stw.y / (var_chunksize * var_chunksize));
    auto coord_x = ((int)(stw.x / var_chunksize));
    auto coord_y = ((int)(stw.y / var_chunksize));
    if (chunk_x > 0)
        coord_x = coord_x - (var_chunksize * chunk_x);
    if (chunk_y > 0)
        coord_y = coord_y - (var_chunksize * chunk_x);
    for (auto chk : map_queue)
        if (chk.starting_coordinates.x == (float)chunk_x * var_chunksize &&
            chk.starting_coordinates.y == (float)chunk_y * var_chunksize)
        {
            auto z = chk.tiles_in_chunk[coord_x][coord_y];
            switch (z.obj)
            {
                case worldgen::object_type::NONE:
                    break;
                case worldgen::object_type::Hill:
                    return "hill";
                case worldgen::object_type::Forest:
                    return "forest";
            }
        }
    return "No objects found";
}
void AppInit::function_draw_ui(content::content_manager manager)
{
    DrawFPS(10, 10);
    DrawText(to_string(GetFrameTime()).c_str(),10,30,14,WHITE);
    if (IsKeyDown(KEY_A)){
        auto object_draw_text = std::async(std::launch::deferred,&AppInit::function_get_current_obj, this);
        DrawText(object_draw_text.get(), 10, 40, 40, WHITE);
    }
}
uint AppInit::function_check_button_boundaries()
{
    int mouse_x = GetMouseX();
    int mouse_y = GetMouseY();
    for (auto bttn : gm.button_storage)
    {
        bool lower_border = (mouse_x > bttn.location.x && mouse_y > bttn.location.y + height);
        bool higher_border = (mouse_x < bttn.location.x + 32 && mouse_y < height + bttn.location.y + 32);
        if (lower_border && higher_border)
            return bttn.id;
    }
    return 0;
}