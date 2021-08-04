#pragma once
struct constants{
    const int screensize = 1024;
    //MapSize - size in tiles!
    const int MapSize = 2;
    //size of tile in px!
    const int tilesize = 32;
    // size - size in tiles. e.g 32 tile units, thus one chunk is made out of 32 tiles which are of 32px size;
    const int chunksize = tilesize;
    const int FPS = 120;
    int seed = 0;
};