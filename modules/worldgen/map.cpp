#include <tuple>
#include "map.h"
constexpr int var_mapsize = constants::mapsize;
constexpr int var_chunksize = constants::chunksize;
world_map::world_map() {
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