#include "tile.h"
#include <vector>
class chunk {

public:
    chunk();
    std::vector<tile> tiles;
    std::vector<chunk> create_chunks();
};
