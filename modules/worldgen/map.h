#include <cmath>
#include <utils/FastNoiseLite.h>
#include <map>
#include "chunk.h"
#include "../../constants.h"
#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
class world_map {
public:
    world_map();
    void function_create_map();
    std::map<std::tuple<int,int>,chunk> chunk_map;
    FastNoiseLite noise;
    void function_sql_save_map();
private:
    int function_sql_conn_check();
    void function_sql_load_map();
    typedef int (*sqlite3_callback)(
        void*,    /* Data provided in the 4th argument of sqlite3_exec() */
        int,      /* The number of columns in row */
        char**,   /* An array of strings representing fields in the row */
        char**    /* An array of strings representing column names */
    );
    terrain_type assign_terrain(float z, float hum, float temp);
    float assign_temp(float z);
    float assign_hum(float z, float temp);
    object_type assign_obj(terrain_type var_terrain);
};
