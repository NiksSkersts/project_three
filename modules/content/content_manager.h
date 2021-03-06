//Place define here - first header in the chain
#define DEBUG_MODE  true
#define GRAPHICS_API_OPENGL_33

namespace content{
    class content_manager{
    public:
        //images
        Image border;
        Image grass;
        Image water;
        Image mountain;
        Image button_build_img;
        //textures
        Texture2D border_texture;
        Texture2D grass_texture;
        Texture2D water_texture;
        Texture2D mountain_texture;
        Texture2D button_build_texture;

        content_manager(){
            function_load_textures();
        }
        void function_unload_textures(){
            UnloadTexture(grass_texture);
            UnloadTexture(water_texture);
            UnloadTexture(button_build_texture);
            UnloadTexture(mountain_texture);
            UnloadTexture(border_texture);
        }
        void function_load_textures()
        //Load textures on app init;
        //todo create texture atlas and implement dynamic tile render.
        {
            //images
            border = GenImageColor(32,32,WHITE);
            grass = LoadImage("../assets/png/grass.png");
            water = LoadImage("../assets/png/water.png");
            mountain = LoadImage("../assets/png/mountain.png");
            //button_images
            button_build_img = LoadImage("../assets/png/button_build.png");
            //textures
            border_texture = LoadTextureFromImage(border);
            grass_texture = LoadTextureFromImage(grass);
            water_texture = LoadTextureFromImage(water);
            mountain_texture = LoadTextureFromImage(mountain);
            //button_textures
            button_build_texture = LoadTextureFromImage(button_build_img);
            //unload - img no longer needed;
            UnloadImage(grass);
            UnloadImage(border);
            UnloadImage(water);
            UnloadImage(mountain);
            UnloadImage(button_build_img);
        }
    };

}
