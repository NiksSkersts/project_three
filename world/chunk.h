#include "tile.h"
#include <vector>
#include "objects.h"

class chunk {

public:
    std::vector<tile> tiles;
    chunk(int x, int y);
    static std::vector<chunk> create_chunks(int x, int y);
    static std::vector<map_object> create_objects(int x, int y);
};
