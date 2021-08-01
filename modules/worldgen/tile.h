#include <raylib.h>
#include "terrain_type.h"

struct tile
{
    tile(Vector3 coordinates,terrain_type terrainType,float hum,float temp) {
        this->coordinates=coordinates;
        this->type = terrainType;
        this->humidity = hum;
        this->temperature = temp;
    }

    Vector3 coordinates;
    terrain_type type;
    float humidity;
    float temperature;
};