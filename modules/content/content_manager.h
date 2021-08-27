#include "raylib.h"

namespace content{
    class content_manager{
    public:
        content_manager(){
            function_load_textures();
        }
        void function_unload_textures(){
            UnloadTexture(grass_texture);
            UnloadTexture(water_texture);
            UnloadTexture(button_build_texture);
            UnloadTexture(mountain_texture);
        }
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
    private:
        void function_load_textures()
        //Load textures on app init;
        {
            //images
            grass = LoadImage("../assets/png/grass/grass_sprite_sheet.png");
            water = LoadImage("../assets/png/water/water_sprite_sheet.png");
            mountain = LoadImage("../assets/png/mountain.png");
            //button_images
            button_build_img = LoadImage("../assets/png/button_build.png");
            //textures
            grass_texture = LoadTextureFromImage(grass);//atlas
            water_texture = LoadTextureFromImage(water);//atlas
            mountain_texture = LoadTextureFromImage(mountain);//single
            //button_textures
            button_build_texture = LoadTextureFromImage(button_build_img);//single
            //unload - img no longer needed;
            UnloadImage(grass);
            UnloadImage(water);
            UnloadImage(mountain);
            UnloadImage(button_build_img);
        }
    };

}
