#include <raylib.h>
#include <vector>
#include <string>
#include "tile.h"
#include <memory>
#include <array>

namespace worldgen{
    class chunk{
    public:
        static constexpr int var_chunksize {32};
        chunk(Vector2 coords);
        std::array<std::array<tile,32>,32> tiles_in_chunk;
        //chunk_id for sqlite db. Create on chunk create to avoid doing it later
        int chunk_id;
        Vector2 starting_coordinates;
        void function_create_tiles(Vector2 vector2);
    };
}