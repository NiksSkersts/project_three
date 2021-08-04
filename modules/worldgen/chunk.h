#include <raylib.h>
#include <vector>
#include "tile.h"

class chunk {
public:
    chunk(Vector2 coords) {
        starting_coordinates = coords;
    }

    std::vector<tile> tiles_in_chunk;
    Vector2 starting_coordinates;
};