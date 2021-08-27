#include <cmath>
#include <map>
#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <tuple>
#include "chunk.h"

namespace worldgen{
    class world_map {
    public:
        world_map();
        void function_create_map();
        std::map<std::tuple<int,int>,chunk> chunk_map;
        void function_sql_map(int function);
        static constexpr int var_mapsize {32};
        int var_chunksize = chunk::var_chunksize;
    private:
        //todo create db if (db!=exist)
        void function_sql_create_db();
        int function_sql_conn_check();
        void subfunction_sql_load_chunk(int i, int j);
        typedef int (*sqlite3_callback)(
                void*,    /* Data provided in the 4th argument of sqlite3_exec() */
                int,      /* The number of columns in row */
                char**,   /* An array of strings representing fields in the row */
                char**    /* An array of strings representing column names */
                );
        void function_sql_open_connection();
        void subfunction_sql_save_chunk(chunk chunk);
        void subfunction_sql_ls_chunk(int function);
        void subfunction_sql_save_tiles(tile t, int id);
        void function_sql_close_connection();
        void function_sql_fin_stmt();
        void subfunction_sql_ls_tiles(chunk *ch, int function);
        void subfunction_sql_load_tiles(chunk *ch, int k, int l);
    };
}
