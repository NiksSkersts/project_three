#include "border_chunk.h"
#include "tile.h"
#include <string>
#include <iostream>
#include <array>

namespace worldgen{
    class chunk{
    public:
        chunk(Vector2 coords,border_chunk border);
        static constexpr int var_chunksize {32};
        //chunk_id for sqlite db. Create on chunk create to avoid doing it later
        unsigned long long int chunk_id;
        Vector2 starting_coordinates;
        void function_create_tiles(Vector2 vector2, border_chunk borderChunk);
        static int function_create_chunk_id(int x, int y);
        std::array<std::array<std::unique_ptr<tile>,32>,32> tiles_in_chunk;
    };
    class chunk_texture_map{
    public:
        chunk_texture_map(chunk &chunk, content::content_manager &contentManager){
            for (int i = 0; i < chunk.var_chunksize; ++i) {
                for (int j = 0; j < chunk.var_chunksize; ++j) {
                    switch(chunk.tiles_in_chunk[i][j]->type) {
                        case terrain_type::water:
                            texture_map[i][j] = std::unique_ptr<Texture2D>(&contentManager.water_texture);
                            break;
                        case terrain_type::border:
                            texture_map[i][j] = std::unique_ptr<Texture2D>(&contentManager.border_texture);
                            break;
                        default:
                            texture_map[i][j] = std::unique_ptr<Texture2D>(&contentManager.grass_texture);
                            break;
                    }
                    switch(chunk.tiles_in_chunk[i][j]->obj) {
                        case object_type::Hill:
                            object_map[i][j] = std::unique_ptr<Texture2D>(&contentManager.mountain_texture);
                            break;
                        case object_type::Forest:
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
        std::array<std::array<std::unique_ptr<Texture2D>,chunk::var_chunksize>,chunk::var_chunksize> texture_map;
        std::array<std::array<std::unique_ptr<Texture2D>,chunk::var_chunksize>,chunk::var_chunksize> object_map;
    };
}