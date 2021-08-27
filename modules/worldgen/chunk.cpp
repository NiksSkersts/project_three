#include "chunk.h"
worldgen::chunk::chunk(Vector2 coords){
    starting_coordinates = coords;
    function_create_tiles(coords);
    //chunk id init
    std::string s2 = std::to_string((int)coords.y);
    std::string result;
    if (coords.x!=0)
        //Sqlite doesn't like integers starting with 0 and drops them;
    {
        std::string s1 = std::to_string((int)coords.x);
        if(coords.y!=0)
            //Just * 10 to represent 0 as y coord else combine strings. eg 32+34 = 3234;
        {
            result = s1+s2;
            chunk_id = std::stoi(result);
        }
        else{
            chunk_id = coords.x*10;
        }
    }else{
        chunk_id = std::stoi(s2);
    }
}
void worldgen::chunk::function_create_tiles(Vector2 vector2) {
    for (int x = 0; x< var_chunksize;++x){
        for(int y = 0; y<var_chunksize;++y){
                Vector2 s_cords = {(float)(vector2.x*var_chunksize)+x,(float)(vector2.y*var_chunksize)+y};
                tiles_in_chunk[x][y] = tile(s_cords);
        }
    }
}

