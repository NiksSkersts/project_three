#include "AppInit.h"
#include <raylib.h>
#include <thread>
#include <vector>
#include <iostream>
using namespace std;
world_map worldMap;
vector<chunk> map_queue;
game_ui gm;
constexpr int var_chunksize = constants::chunksize;
constexpr int var_mapsize = constants::mapsize;
constexpr int var_seed = constants::seed;
constexpr int var_fps = constants::FPS;
constexpr int var_tilesize = constants::tilesize;
AppInit::AppInit()
// Opengl window init, map init and some basic config;
// Textures must be handled after OpenGL init!
{
  width = GetScreenWidth() / 2;
  height = GetScreenHeight() / 2;
  // fallback values
  if (width == 0)
    width = 500;
  if (height == 0)
    height = 500;
  InitWindow(width, height, "project_two");
  content_manager cm;
  SetTargetFPS(var_fps);
  SetExitKey(27);
  // init noise settings;
  worldMap.noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
  worldMap.noise.SetSeed(var_seed);
  // end init;
  function_add_chunks_to_queue();
  initCamera();
  gameLoop(cm);
}
void AppInit::initCamera()
// Camera init
{
  camera2D.target = {GetScreenWidth() + 20.0f, GetScreenHeight() + 20.0f};
  camera2D.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
  camera2D.rotation = 0.0f;
  camera2D.zoom = 2.0f;
}
void AppInit::gameLoop(content_manager manager)
// Base gameloop and de-init when the while loop breaks;
{
  while (!WindowShouldClose())
  {
    update();
    draw(manager);
  }
  // de-init part
  manager.function_unload_textures();
  CloseWindow();
}
void AppInit::update()
// Update part of the loop. For variable, camera  updates and so on;
{
  // update window size for responsive layout;
  height = GetScreenHeight();
  width = GetScreenWidth();
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
    }
    break;
  }
}
void AppInit::draw(content_manager manager)
// Draw part of the loop. Rendering part
{
  ClearBackground(BLACK);
  BeginDrawing();
  BeginMode2D(camera2D);
  for (auto chk : map_queue)
    for (int i = 0; i < var_chunksize; ++i)
      for (int j = 0; j < var_chunksize; ++j)
      {
        auto t = *chk.tiles_in_chunk[i][j];
        switch (t.type)
        {
        case terrain_type::grass:
          function_call_draw_texture(manager.grass_texture,
                                     (t.coordinates.x * var_tilesize),
                                     (t.coordinates.y * var_tilesize), WHITE);
          break;
        case terrain_type::water:
          function_call_draw_texture(manager.water_texture,
                                     (t.coordinates.x * var_tilesize),
                                     (t.coordinates.y * var_tilesize), WHITE);
          break;
        case terrain_type::hills:
          function_call_draw_texture(manager.grass_texture,
                                     (t.coordinates.x * var_tilesize),
                                     (t.coordinates.y * var_tilesize), WHITE);
          break;
        case terrain_type::forest:
          // temp
          function_call_draw_texture(manager.grass_texture,
                                     (t.coordinates.x * var_tilesize),
                                     (t.coordinates.y * var_tilesize), WHITE);
          break;
        }
        switch (t.obj)
        {
        case object_type::NONE:
          break;
        case object_type::Forest:
          break;
        case object_type::Hill:
          DrawTexture(manager.mountain_texture,
                      (t.coordinates.x * var_tilesize),
                      (t.coordinates.y * var_tilesize), Fade(WHITE, 1.0f));
          break;
        }
      }
  EndMode2D();
  // functions
  function_draw_ui(manager);
  if (IsKeyDown(KEY_A))
  {
    // creates a software thread. Delegating threading to OS instead of HW;
    auto i = std::async(std::launch::deferred,
                        &AppInit::function_get_current_obj, this);
    DrawText(i.get(), 10, 40, 40, WHITE);
  }
  EndDrawing();
}
void AppInit::function_add_chunks_to_queue()
// load chunks into a vector;
// Vector will be used to limit the amount of loaded chunks;
{
  for (int i = 0; i < var_mapsize; ++i)
    for (int j = 0; j < var_mapsize; ++j)
    {
      auto b = worldMap.chunk_map.find(
          std::tuple(i * var_chunksize, j * var_chunksize));
      auto t = *&b->second;
      map_queue.push_back(t);
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
      auto z = *chk.tiles_in_chunk[coord_x][coord_y];
      switch (z.obj)
      {
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

void AppInit::function_draw_ui(content_manager manager)
{
  DrawFPS(10, 10);
  for (auto buttons : gm.button_storage)
  {
    switch (buttons.buttonType)
    {
    case button_type::button_build:
      function_call_draw_texture(manager.button_build_texture,
                                 buttons.location.x,
                                 height + buttons.location.y, WHITE);
      break;
    }
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
void AppInit::function_call_draw_texture(Texture2D texture, float x, float y, Color col)
// todo add more common code on draw
{
  DrawTexture(texture, x, y, col);
}