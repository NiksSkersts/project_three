#include "map.h"
using namespace worldgen;
sqlite3 *db;
sqlite3_stmt *stmt;
char *zErrMsg = 0;
int rc;

world_map::world_map(content::content_manager &contentManager) {
    //sqlite part moved out to scratch pad; will be redone later
    function_create_map(contentManager);
}
world_map::~world_map(){
}
void world_map::function_create_map(content::content_manager &manager) {
    for (int k = 0; k < var_mapsize; ++k) {
        for (int l = 0; l < var_mapsize; ++l) {
            border_chunk borderChunk = function_determine_border(k,l);
            chunk *ch_temp = new chunk({(float)k*var_chunksize,(float )l*var_chunksize},borderChunk);
            chunk_texture_map *ch_texture = new chunk_texture_map(*ch_temp,manager);
            chunk_and_texture_map.emplace(ch_temp->chunk_id,std::pair(ch_temp,ch_texture));
        }
    }
}
border_chunk world_map::function_determine_border(int k, int l){
    if (k == 0){
        if (l == 0){
            return border_chunk::upper_left_corner;
        }else if(l != var_mapsize -1 ){
            return border_chunk::up;
        }else{
            return border_chunk::upper_right_corner;
        }
    }else if(k>0 && k != var_mapsize -1){
        if (l == 0){
            return border_chunk::left;
        }else if(l == var_mapsize -1){
            return border_chunk::right;
        }
    }else if (k == var_mapsize -1){
        if(l == 0){
            return border_chunk::bottom_left_corner;
        }else if (l > 0 && l != var_mapsize -1){
            return border_chunk::bottom;
        }else if (l == var_mapsize -1){
            return border_chunk::bottom_right_corner;
        }
    }else{
        return border_chunk::none;
    }
    return border_chunk::none;
}

