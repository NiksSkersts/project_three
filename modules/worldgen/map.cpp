#include <tuple>
#include "map.h"
#include <iostream>
constexpr int var_mapsize = constants::mapsize;
constexpr int var_chunksize = constants::chunksize;
sqlite3 *db;
char *zErrMsg = 0;
int rc;
world_map::world_map() {
    auto code = function_sql_conn_check();
    if (code ==0)
    {
        function_create_map(); 
        return;
    }
    exit(code);
    function_sql_load_map();
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
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    int count = 0;
    rc = sqlite3_open("../project_two.db",&db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
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
    sqlite3_close(db);
    return 0;
}
void world_map::function_sql_load_map(){
}

void world_map::function_sql_save_map(){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *zErrMsg = 0;
    int result_code;
    int count = 0;
    //conn was checked at app entry;
    result_code = sqlite3_open("../project_two.db",&db);
    if(result_code != SQLITE_OK) function_sql_conn_check();
    for (int i = 0; i < var_mapsize; ++i)
    for (int j = 0; j < var_mapsize; ++j)
    {
      auto b = chunk_map.find(std::tuple(i * var_chunksize, j * var_chunksize));
      auto t = *&b->second.tiles_in_chunk;
      for (int k =0;k<32;++k)
          for(int l=0;l<32;++l){
              tile *tile = *&t[k][l];
              auto sas = tile->coordinates.x;
              sqlite3_prepare_v2(db,"INSERT INTO world_map (x, y, terrainType, temperature, humidity, objectType,z) VALUES(?1, ?2, ?3, ?4, ?5, ?6, ?7);",-1,&stmt,NULL);
              result_code = sqlite3_bind_int( stmt, 1, (int)tile->coordinates.x);
              result_code = sqlite3_bind_int( stmt, 2, (int)tile->coordinates.y);
              result_code = sqlite3_bind_int( stmt, 3, (int)static_cast<int>(tile->type));
              result_code = sqlite3_bind_double( stmt, 4, tile->temperature);
              result_code = sqlite3_bind_double( stmt, 5, tile->humidity);
              result_code = sqlite3_bind_int( stmt, 6, (int)static_cast<int>(tile->obj));
              result_code = sqlite3_bind_double( stmt, 7, tile->coordinates.z);
              result_code = sqlite3_step( stmt );
              result_code = sqlite3_clear_bindings( stmt );
              result_code = sqlite3_reset( stmt );
              result_code = sqlite3_finalize( stmt );  //  Finalize the prepared statement.
          }
    }
}