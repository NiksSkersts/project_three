#include "modules/worldgen/map.h"
namespace ui{
    class AppInit {
    public:
        bool game{true};
        AppInit();
    private:
        static constexpr int var_chunksize {worldgen::chunk::var_chunksize};
        static constexpr int var_fps {240};
        int var_upd_range{100};
        bool reload_map {true};
        Vector2 old_coordinates{0,0};
        Camera2D camera2D;
        std::array<std::pair<std::array<worldgen::chunk *,3>,std::array<worldgen::chunk_texture_map *,3>>,3> map_temp_storage;

        inline void base_settings();
        inline void init_camera();
        inline void game_loop();
        void update(worldgen::world_map &map);
        void function_add_chunks_to_queue(worldgen::world_map *map);
        void draw();
        bool function_map_should_update();
        void function_get_keypress();
    };
}
