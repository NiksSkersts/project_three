#include <raylib.h>
#include <basics/constants.h>
#include <modules/worldgen/map.h>

class AppInit {
private:
    int width;
    int height;
    void initCamera();
    void gameLoop();
    Camera3D camera3D;
    Camera2D camera2D;


    //images
    Image grass;
    Image water;
    Image mountain;
    Image button_build_img;
    //textures
    Texture2D grass_texture;
    Texture2D water_texture;
    Texture2D mountain_texture;
    Texture2D button_build_texture;

public:
    AppInit();
private:
    void update();
    void draw();

    const char * function_get_current_obj();

    void function_add_chunks_to_queue();

    void function_load_textures();
};
