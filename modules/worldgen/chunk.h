#include <raylib.h>
#include <vector>
#include <string>
#include "tile.h"
namespace worldgen{
    class chunk {
    public:
        chunk(Vector2 coords) {
            starting_coordinates = coords;
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
        //chunk_id meant for sqlite db. Create on chunk create to avoid doing it later
        int chunk_id;
        tile *tiles_in_chunk[32][32];
        Vector2 starting_coordinates;
    };
}