#include "tile.h"
#include <string>
#include <iostream>
#include <array>

namespace worldgen{
    class chunk {
    public:
        enum border_chunk{
            upper_left_corner,
            left,
            bottom_left_corner,
            up,
            bottom,
            upper_right_corner,
            right,
            bottom_right_corner,
            none
        };

        chunk(Vector2 coords, border_chunk border);

        static constexpr int var_chunksize{32};
        //chunk_id for sqlite db. Create on chunk create to avoid doing it later
        unsigned long long int chunk_id;
        Vector2 starting_coordinates;
        std::array<std::array<std::unique_ptr<tile>, 32>, 32> tiles_in_chunk;

        void function_create_tiles(Vector2 vector2, border_chunk borderChunk);

        static int function_create_chunk_id(int x, int y);
    };

    class chunk_texture_map{
    public:
        std::array<std::array<Texture2D *,chunk::var_chunksize>,chunk::var_chunksize> texture_map;
        std::array<std::array<Texture2D *,chunk::var_chunksize>,chunk::var_chunksize> object_map;

        chunk_texture_map(chunk &chunk, content::content_manager &contentManager){
            for (int i = 0; i < chunk.var_chunksize; ++i) {
                for (int j = 0; j < chunk.var_chunksize; ++j) {
                    switch(chunk.tiles_in_chunk[i][j]->type) {
                        case tile::terrain_type::water:
                            texture_map[i][j] = &contentManager.water_texture;
                            break;
                        case tile::terrain_type::border:
                            texture_map[i][j] = &contentManager.border_texture;
                            break;
                        default:
                            texture_map[i][j] = &contentManager.grass_texture;
                            break;
                    }
                    switch(chunk.tiles_in_chunk[i][j]->obj) {
                        case tile::object_type::Hill:
                            object_map[i][j] = &contentManager.mountain_texture;
                            break;
                        case tile::object_type::Forest:
                            // todo implement forest
                            object_map[i][j] = nullptr;
                            break;
                        default:
                            object_map[i][j] = nullptr;
                            break;
                    }
                }
            }
        }
    };
}