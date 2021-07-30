#include <vector>
#include "chunk.h"
#include "../basics/constants.h"

constants c;
std::vector<map_object>  objs;
std::vector<chunk> chunks;

//inits a single chunk unit that is in turn made out of 32 tiles.
// x = chunk unit that's multiplied by 32+1. 
// on x_0 = 0*(33);y_0 = 0*33 tiles will be added to the list starting with x0;y0 and ending with x0+32;y0+33 thus creating 32x32 chunk
// on x_1 = 33;y_1 = 33 :: (33;33) and ending with (64;64) thus creating 32x32 chunk. 33;33, because 32;32 was already added on (0;0) chunk.
chunk::chunk(int x, int y) {
    tiles.reserve(c.ChunkSize*c.ChunkSize);
    for (int i = x*(c.ChunkSize+1); i < (x*c.ChunkSize)+ c.ChunkSize; ++i) {
        for (int j = y*(c.ChunkSize+1); j < (y*c.ChunkSize)+ c.ChunkSize; ++j) {
            tiles.emplace_back(tile(i,j));
        }
    };
}
//creates multiple chunks that will be used to render chunks around player location. 3x3 : 5 being the central chunk. big math. =)
// int x, y represent chunks in chunk units. one chunk is made out of 32x32 tiles where a tile is 32x32 px.
//thus one chunk unit is px from camera divided by 32 and then divided again by 32.
std::vector<chunk> chunk::create_chunks(int x, int y)
{
    chunks.reserve(c.WorldSize*c.WorldSize);
    x = ((x/c.ChunkSize)/c.ChunkSize);
    y = ((y/c.ChunkSize)/c.ChunkSize);
    for (int i = x-1; i < x + 2; i++) {
        for (int j = y-1; j < y + 2; j++)
        {
            chunks.emplace_back(chunk(i,j));
        }
    }
    return chunks;
}
