#include <raylib.h>
#include <modules/worldgen/map.h>
#include <modules/content/content_manager.h>
#include <queue>
#include <modules/ui/game_ui.h>
#include <future>
#include <thread>
#include <raylib.h>
#include <vector>
#include <iostream>
namespace main_logic{
    class AppInit {
    public:
        int width;
        int height;
        AppInit();
    private:
        void initCamera();
        void gameLoop(content::content_manager &manager);
        Camera2D camera2D;
        void update();
        const char * function_get_current_obj();
        void function_add_chunks_to_queue();
        void draw(content::content_manager manager);
        void function_draw_ui(content::content_manager manager);
        uint function_check_button_boundaries();
        void function_get_keypress();
        bool function_map_should_update();
        void function_draw_map(content::content_manager manager, worldgen::tile);
    };
}
