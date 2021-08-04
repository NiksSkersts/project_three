#include <tuple>
#include "map.h"
FastNoiseLite noise;
world_map::world_map(constants c) {
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
    noise.SetSeed(c.seed);
    for (int x = 0; x< c.MapSize;++x)
        for(int y = 0; y<c.MapSize;++y)
        {
            std::tuple<int,int> current_chunk = {round(x/32), round(y/32)};
            if (fmod(x,c.tilesize)==0&& fmod(y,c.tilesize)==0)
                //chunk contains 32 tiles, thus if I divide by 32 and it returns with a remainder, then the program is trying to load a chunk on another chunk.
                //chunk over another chunk - bad for business, bad for FPS.
            {
                Vector2 s_cords = {(float)std::get<0>(current_chunk),(float)std::get<1>(current_chunk)};
                chunk_map.emplace(std::tuple(x,y),chunk(s_cords));
            }
            //sec_check if var noise ! x>= -1  AND !x <= 1 : Do it again.
            sec_check:
            float var_noise = noise.GetNoise((float)x,(float)y);
            if ((var_noise>=-1 && var_noise <=1)!= true) goto sec_check;
            //3D vector coords rounded to nearest integer, except for z as will always be -1>=x<=1;
            Vector3 var_coords = {roundf(x),roundf(y),var_noise};
            float var_temperature = assign_temp(var_noise);
            float var_humidity = assign_hum(var_noise,var_temperature);
            terrain_type var_terrain = assign_terrain(var_noise,var_humidity,var_temperature);
            //objects that are added on world creation - e.g trees;
            object_type var_obj = object_type::NONE;
            if (var_terrain==terrain_type::forest || var_terrain==terrain_type::hills)
                var_obj = assign_obj(var_terrain);
            chunk_map.find(current_chunk)->second.tiles_in_chunk.push_back(tile(var_coords,var_terrain,var_humidity,var_temperature,var_obj));
        }

}
terrain_type world_map::assign_terrain(float z, float hum, float temp) {
    if (z <= 0) return terrain_type::water;
    if (z > 0) {
        if (hum > 0 && temp > 0) return  terrain_type::grass;
        else return terrain_type::hills;
    }
    if (z<0) return terrain_type::water;
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
            break;
            case terrain_type::forest:
                return object_type::Forest;
                break;
                default:
                    return object_type::NONE;
                    break;
    };
}
