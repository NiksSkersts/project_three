//
// Created by skers on 28/07/2021.
//

#include <vector>
#include "chunk.h"
#include "constants.h"

chunk::chunk() {
    constants c;
    this->tiles;
    for (int32_t i = 0; i < c.ChunkSize+1; ++i) {
        for (int32_t j = 0; j < c.ChunkSize+1; ++j) {
            tiles.emplace_back(tile(i,j));
        }
    };
}
std::vector<chunk> chunk::create_chunks()
{
    constants c;
    std::vector<chunk> chunks;
    for (int x = 0; x < c.WorldSize; x++) {
        for (int y = 0; y < c.WorldSize; y++)
        {
            chunks.emplace_back(chunk());
        }
    }
    return chunks;
}
