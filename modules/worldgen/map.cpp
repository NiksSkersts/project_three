#include <tuple>
#include "map.h"
#include <iostream>
constexpr int var_mapsize = constants::mapsize;
constexpr int var_chunksize = constants::chunksize;
sqlite3 *db;
sqlite3_stmt *stmt;
char *zErrMsg = 0;
int rc;
world_map::world_map() {
    auto code = function_sql_conn_check();
    if (code ==0)
    {
        function_create_map(); 
        return;
    }else{
        //int 0 save map;
        //int 1 load map;
        function_sql_map(1);
    }
}
void world_map::function_create_map(){
        for (int k = 0; k < var_mapsize; ++k) {
        for (int l = 0; l < var_mapsize; ++l) {
            chunk_map.emplace(std::tuple((int)k*var_chunksize,(int)l*var_chunksize),chunk({(float)k*var_chunksize,(float )l*var_chunksize}));
            for (int x = 0; x< var_chunksize;++x)
                for(int y = 0; y<var_chunksize;++y)
                {
                    Vector2 s_cords = {(float)(k*var_chunksize)+x,(float)(l*var_chunksize)+y};
                    //sec_check if var noise ! x>= -1  AND !x <= 1 : Do it again.
                    sec_check:
                    float var_noise = noise.GetNoise((float)s_cords.x,(float)s_cords.y);
                    if ((var_noise>=-1 && var_noise <=1)!= true) goto sec_check;
                    //3D vector coords rounded to nearest integer, except for z as it will always be -1>=x<=1;
                    Vector3 var_coords = {roundf(s_cords.x),roundf(s_cords.y),var_noise};
                    float var_temperature = assign_temp(var_noise);
                    float var_humidity = assign_hum(var_noise,var_temperature);
                    terrain_type var_terrain = assign_terrain(var_noise,var_humidity,var_temperature);
                    //objects that are added on world creation - e.g trees;
                    object_type var_obj = object_type::NONE;
                    if (var_terrain==terrain_type::forest || var_terrain==terrain_type::hills)
                        var_obj = assign_obj(var_terrain);
                    chunk_map.find(std::tuple((int)k*var_chunksize,(int)l*var_chunksize))->second.tiles_in_chunk[x][y] = new tile(var_coords,var_terrain,var_humidity,var_temperature,var_obj);
                }
        }
    }
}
terrain_type world_map::assign_terrain(float z, float hum, float temp) {
    if (z <= 0) return terrain_type::water;
    if (hum > 0 && temp > 0 && z < 0.5) return  terrain_type::grass;
    if(z >= 0.5) return terrain_type::hills;
    return terrain_type::grass;
}
float world_map::assign_temp(float z)
{
    return cosf(z);
}
float world_map::assign_hum(float z, float temp)
{
    return ((temp*z+1)/(2));
}
object_type world_map::assign_obj(terrain_type var_terrain)
//todo implement object_type::forest && terrain_type::forest
{
    switch (var_terrain) {
        case terrain_type::hills:
            return object_type::Hill;
            case terrain_type::forest:
                return object_type::Forest;
                default:
                    return object_type::NONE;
    };
}
static int callback(void *count, int argc, char **argv, char **azColName) {
    int *c = static_cast<int *>(count);
    *c = atoi(argv[0]);
    return 0;
}
int world_map::function_sql_conn_check(){
    int count = 0;
    function_sql_open_connection();
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        function_sql_close_connection();
        return(1);
    }
    rc = sqlite3_exec(db, "select count(*) from world_map", callback, &count, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("count: %d\n", count);
        return count;
    }
    function_sql_close_connection();
    return 0;
}
void world_map::function_sql_map(int function){
    function_sql_open_connection();
    subfunction_sql_ls_chunk(function);
    function_sql_close_connection();
}
void world_map::function_sql_open_connection(){
    rc = sqlite3_open("../project_two.db",&db);
    //conn was checked at app entry and should be OK!
    //if not, check again and throw err.
    if(rc != SQLITE_OK) function_sql_conn_check();
}
void world_map::function_sql_close_connection(){sqlite3_close(db);}
void world_map::subfunction_sql_ls_chunk(int function){
    //todo
    for (int i = 0; i < var_mapsize; ++i)
        for (int j = 0; j < var_mapsize; ++j){
            if (function == 1)
                subfunction_sql_load_chunk(i, j);
            if (function == 0){
                auto b = chunk_map.find(std::tuple(i * var_chunksize, j * var_chunksize));
                if (b.operator->() == nullptr) std::cout<<"shouldn't happen: "+ std::to_string(i)+ std::to_string(j);
                subfunction_sql_save_chunk(b->second);
            }
        }
}
void world_map::subfunction_sql_save_chunk(chunk chunk) {
    sqlite3_prepare_v2(db,"INSERT INTO chunk (x, y, chunk_id) VALUES(?1, ?2, ?3);",-1,&stmt,NULL);
    rc = sqlite3_bind_int( stmt, 1, (int)chunk.starting_coordinates.x);
    rc = sqlite3_bind_int( stmt, 2, (int)chunk.starting_coordinates.y);
    rc = sqlite3_bind_int( stmt, 3, (int)chunk.chunk_id);
    rc = sqlite3_step( stmt );
    rc = sqlite3_clear_bindings( stmt );
    rc = sqlite3_reset( stmt );
    rc = sqlite3_finalize( stmt );
    subfunction_sql_ls_tiles(&chunk,0);
}
void world_map::subfunction_sql_load_chunk(int i, int j) {
    sqlite3_prepare_v2(db,"SELECT x, y, chunk_id FROM chunk WHERE x=?1 AND y=?2;",-1,&stmt,NULL);
    rc = sqlite3_bind_int(stmt,1,(int)i*var_chunksize);
    rc = sqlite3_bind_int(stmt,2,(int)j*var_chunksize);
    rc = sqlite3_step( stmt );
    auto ch = new chunk({(float)sqlite3_column_int(stmt,0), (float)sqlite3_column_int(stmt,1)});
    subfunction_sql_ls_tiles(*&ch, 1);
    chunk_map.emplace(std::tuple(ch->starting_coordinates.x, ch->starting_coordinates.y),*ch);
    function_sql_fin_stmt();
}
void world_map::function_sql_fin_stmt(){
    rc = sqlite3_clear_bindings( stmt );
    rc = sqlite3_reset( stmt );
    if(rc == SQLITE_DONE)
        rc = sqlite3_finalize( stmt );
}
void world_map::subfunction_sql_ls_tiles(chunk *ch, int function) {
    for (int k =0;k<32;++k)
        for(int l=0;l<32;++l){
            if (function==0) subfunction_sql_save_tiles(*ch->tiles_in_chunk[k][l],ch->chunk_id);
            if (function==1) subfunction_sql_load_tiles(ch,k,l);
        }
}
void world_map::subfunction_sql_save_tiles(tile t,int id){
    sqlite3_prepare_v2(db,"INSERT INTO world_map (chunk_id, x, y, z, objectType, terrainType, humidity, temperature) VALUES(?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8);",-1,&stmt,NULL);
    rc = sqlite3_bind_int( stmt, 1, (int)id);
    rc = sqlite3_bind_int( stmt, 2, (int)t.coordinates.x);
    rc = sqlite3_bind_int( stmt, 3, (int)t.coordinates.y);
    rc = sqlite3_bind_double( stmt, 4, t.coordinates.z);
    rc = sqlite3_bind_int( stmt, 5, (int)static_cast<int>(t.obj));
    rc = sqlite3_bind_int( stmt, 6, (int)static_cast<int>(t.type));
    rc = sqlite3_bind_double( stmt, 7, t.humidity);
    rc = sqlite3_bind_double( stmt, 8, t.temperature);
    rc = sqlite3_step( stmt );
    rc = sqlite3_clear_bindings( stmt );
    rc = sqlite3_reset( stmt );
    rc = sqlite3_finalize( stmt );
}
void world_map::subfunction_sql_load_tiles(chunk *ch, int k, int l) {
    sqlite3_prepare_v2(db,"SELECT chunk_id, x, y, z, objectType, terrainType, humidity, temperature FROM world_map WHERE x=?1 AND y=?2;",-1,&stmt,NULL);
    rc = sqlite3_bind_int(stmt,1,(int)(ch->starting_coordinates.x)+k);
    rc = sqlite3_bind_int(stmt,2,(int)(ch->starting_coordinates.y)+l);
    rc = sqlite3_step( stmt );
    Vector3 coords = {(float)sqlite3_column_int(stmt,1),(float)sqlite3_column_int(stmt,2),(float)sqlite3_column_double(stmt,3)};
    auto obj = static_cast<object_type>(sqlite3_column_int(stmt,4));
    auto type= static_cast<terrain_type>(sqlite3_column_int(stmt,5));
    auto hum = (float)sqlite3_column_double(stmt,6);
    auto temp = (float)sqlite3_column_double(stmt,7);
    ch->tiles_in_chunk[k][l] = new tile(coords,type,hum,temp,obj);
    function_sql_fin_stmt();
}
void world_map::function_sql_create_db()
//create a db if it is missing in the root of the folder.
{
    //todo
}
