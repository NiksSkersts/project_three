#include "chunk.h"
worldgen::chunk::chunk(Vector2 coords,border_chunk border){
    starting_coordinates = coords;
    border_chunk borderChunk = border;
    function_create_tiles(coords, borderChunk);
    chunk_id = function_create_chunk_id(coords.x,coords.y);
}
void worldgen::chunk::function_create_tiles(Vector2 vector2, border_chunk borderChunk) {
    for (int x = 0; x< var_chunksize;++x){
        for(int y = 0; y<var_chunksize;++y) {
            Vector2 s_cords = {(float) (vector2.x) + x, (float) (vector2.y) + y};
            switch (borderChunk) {
                //todo find a better way to do this!
                case border_chunk::upper_left_corner:
                    if (x == 0 || y == 0) {
                        tiles_in_chunk[x][y] = std::unique_ptr<tile>(new tile(s_cords, true));
                    } else {
                        tiles_in_chunk[x][y] = std::unique_ptr<tile>(new tile(s_cords));
                    }
                    break;
                case border_chunk::left:
                    if (y == 0) {
                        tiles_in_chunk[x][y] = std::unique_ptr<tile>(new tile(s_cords, true));
                    } else {
                        tiles_in_chunk[x][y] = std::unique_ptr<tile>(new tile(s_cords));
                    }
                    break;
                case border_chunk::bottom_left_corner:
                    if (y == 0 || x == var_chunksize - 1) {
                        tiles_in_chunk[x][y] = std::unique_ptr<tile>(new tile(s_cords, true));
                    } else {
                        tiles_in_chunk[x][y] = std::unique_ptr<tile>(new tile(s_cords));
                    }
                    break;
                case border_chunk::up:
                    if (x == 0) {
                        tiles_in_chunk[x][y] = std::unique_ptr<tile>(new tile(s_cords, true));
                    } else {
                        tiles_in_chunk[x][y] = std::unique_ptr<tile>(new tile(s_cords));
                    }
                    break;
                case border_chunk::bottom:
                    if (x == var_chunksize - 1) {
                        tiles_in_chunk[x][y] = std::unique_ptr<tile>(new tile(s_cords, true));
                    } else {
                        tiles_in_chunk[x][y] = std::unique_ptr<tile>(new tile(s_cords));
                    }
                    break;
                case border_chunk::upper_right_corner:
                    if (x == 0 || y == var_chunksize - 1) {
                        tiles_in_chunk[x][y] = std::unique_ptr<tile>(new tile(s_cords, true));
                    } else {
                        tiles_in_chunk[x][y] = std::unique_ptr<tile>(new tile(s_cords));
                    }
                    break;
                case border_chunk::right:
                    if (y == var_chunksize - 1) {
                        tiles_in_chunk[x][y] = std::unique_ptr<tile>(new tile(s_cords, true));
                    } else {
                        tiles_in_chunk[x][y] = std::unique_ptr<tile>(new tile(s_cords));
                    }
                    break;
                case border_chunk::bottom_right_corner:
                    if (x == var_chunksize - 1 || y == var_chunksize - 1) {
                        tiles_in_chunk[x][y] = std::unique_ptr<tile>(new tile(s_cords, true));
                    } else {
                        tiles_in_chunk[x][y] = std::unique_ptr<tile>(new tile(s_cords));
                    }
                    break;
                case border_chunk::none:
                    tiles_in_chunk[x][y] = std::unique_ptr<tile>(new tile(s_cords));
                    break;
            }
        }
    }
}
int worldgen::chunk::function_create_chunk_id(int x, int y) {
    //chunk id init
    std::string s2 = std::to_string(y);
    std::string result;
    if (x!=0)
        //Sqlite doesn't like integers starting with 0 and drops them;
    {
        std::string s1 = std::to_string(x);
        if(y!=0)
            //Just * 10 to represent 0 as y coord else combine strings. eg 32+34 = 3234;
        {
            result = s1+s2;
            return std::stoi(result);
        }
        else{
            return x*10;
        }
    }else{
        return std::stoi(s2);
    }
}

