#include <raylib.h>
#include <basics/constants.h>
#include <modules/worldgen/map.h>

class AppInit {
private:
    void initCamera();
    void gameLoop();
    Camera3D camera3D;
    Camera2D camera2D;
    Image grass;
    Image water;
    Image mountain;
    Texture2D grass_texture;
    Texture2D water_texture;
    Texture2D mountain_texture;


public:
    AppInit(int w, int h);
private:
    void update();
    void draw();

    void LoadTextures();

    void function_get_current_obj();

    void function_add_chunks_to_queue();
};
