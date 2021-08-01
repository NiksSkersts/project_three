#include <map>
#include <raylib.h>
#include "tile.h"
#include "map"

class chunk {
public:
    chunk(Vector2 startingCoordinates);
//top-left point in chunk
    Vector2 starting_coordinates;
    std::map<std::tuple<float,float>,tile> chunk_array;
private:
    terrain_type assign_terrain(float z, float hum, float temp);

    float assign_temp(float z);

    float assign_hum(float z, float temp);
};