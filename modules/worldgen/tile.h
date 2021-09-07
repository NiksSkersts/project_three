#include <utils/FastNoiseLite.h>
#include <raylib.h>
#include "modules/content/content_manager.h"
#include <cmath>
#include <memory>
#include <vector>

namespace worldgen {
    class tile {
    public:
        enum terrain_type{
            grass,
            water,
            hills,
            forest,
            border
        };
        enum object_type {
            NONE,
            Hill,
            Forest
        };
        //loading from db
        tile(Vector3 coords, terrain_type t_type, float hum, float temp, object_type obj_type);
        //creating border
        tile(Vector2 coords, bool border);
        //creating from scratch
        tile(Vector2 coords);
        //deconstructor
        ~tile();

        //size of a single square tile. Size represents a px!
        static constexpr size_t tilesize{32};
        //coordinates of tile uppermost left corner. Inverse Matrix, thus -y is up and +y is below.
        // z represents height. 0 is middle point. x<0 = water and x>0 is land and later hills. Z range [-1;1]
        Vector3 coordinates;
        //A single tile can have a single terrain type. E.g grass.
        terrain_type type;
        //A single tile can host a single object. I am going for that retro feel, like an old CIV game.
        object_type obj;
        //humidity depends on temperature and height.
        float humidity;
        //depends on height.
        float temperature;
    private:
        static const int var_seed{0};
        FastNoiseLite noise{var_seed};
        void function_init_noise_settings();
        float assign_height(Vector2 coords);
        float assign_temp(float z);
        float assign_hum(float z, float temp);
        terrain_type assign_terrain(float z, float hum, float temp);
        object_type assign_obj(terrain_type var_terrain);
    };
}