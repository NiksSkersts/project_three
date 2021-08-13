#include <raylib.h>
#include <vector>
#include <string>
#include "tile.h"

class chunk {
public:
    chunk(Vector2 coords) {
        starting_coordinates = coords;
        std::string s2 = std::to_string((int)coords.y);
        std::string result;
        if (coords.x!=0){
            std::string s1 = std::to_string((int)coords.x);
            if(coords.y!=0){
                result = s1+s2;
                chunk_id = std::stoi(result);

            }
            else{
                auto x = coords.x*10;
                chunk_id = coords.x*10;
            }
        }else{
            chunk_id = std::stoi(s2);
        }
    }
    int chunk_id;
    tile *tiles_in_chunk[32][32];
    Vector2 starting_coordinates;
};