#include <raylib.h>
#include "terrain_type.h"
#include "object_type.h"
namespace worldgen{
    class tile{
    public:
        tile(Vector3 coordinates,terrain_type terrainType,float hum,float temp,object_type obj) {
            this->coordinates=coordinates;
            this->type = terrainType;
            this->humidity = hum;
            this->temperature = temp;
            this->obj = obj;
        }
        Vector3 coordinates;
        terrain_type type;
        object_type obj;
        float humidity;
        float temperature;
        //render layers is for dynamic tiles. Tile is split into 9x9 currently represented by squares.
        //todo graphics update after important things are done
        std::vector<int> render_layers;

    };
}