#include <cmath>
#include <utils/FastNoiseLite.h>
#include <map>
#include "chunk.h"
#include "../../constants.h"
class world_map {
public:
    world_map();
    std::map<std::tuple<int,int>,chunk> chunk_map;
    terrain_type assign_terrain(float z, float hum, float temp);
    float assign_temp(float z);
    float assign_hum(float z, float temp);
    object_type assign_obj(terrain_type var_terrain);

    FastNoiseLite noise;
};
