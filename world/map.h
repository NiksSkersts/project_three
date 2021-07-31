#include <utility>
#include <map>
#include "tile.h"

class map {
public:
    map();
    static std::map<std::tuple<int, int, int>, tile> create_map(int w, int h);

    static float assign_hum(float z, float temp);

    static float assign_temp(float z);

    static terrain_type assign_terrain(float z, float hum, float temp);
};
