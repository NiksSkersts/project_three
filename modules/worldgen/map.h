#include "chunk.h"
#include <map>
#include <sqlite3.h>
#include <set>

//todo reimplement sqlite db
namespace worldgen{
    class world_map {
    public:
        world_map(content::content_manager &contentManager);
        ~world_map();
        static constexpr int var_mapsize {3};
        static constexpr int var_chunksize = chunk::var_chunksize;
        void function_create_map(content::content_manager &manager);
        std::map<unsigned long long int,std::pair<std::unique_ptr<chunk>,std::unique_ptr<chunk_texture_map>>> chunk_and_texture_map;
    private:
        chunk::border_chunk function_determine_border(int k, int l);
    };
}
