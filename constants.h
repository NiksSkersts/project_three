#pragma once
struct constants
{
    //mapsize - size in tiles!
    static const int mapsize = 32;
    //size of tile in px!
    static const int tilesize = 32;
    // size - size in tiles. e.g 32 tile units, thus one chunk is made out of 32 tiles which are of 32px size;
    static const int chunksize = tilesize;
    static const int FPS = 240;
    static const int seed = 0;
};
