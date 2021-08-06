#include <raylib.h>
#include <vector>
#include "tile.h"

class chunk {
public:
    chunk(Vector2 coords) {
        starting_coordinates = coords;
    }
    tile *tiles_in_chunk[32][32];
    Vector2 starting_coordinates;
};