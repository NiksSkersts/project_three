#include <basics/constants.h>
#include <utils/FastNoiseLite.h>
#include <string>
#include "map.h"

FastNoiseLite noise;
std::map<std::tuple<int,int,int>,tile> world_map;
std::map<std::tuple<int, int, int>, tile> map::create_map(int w, int h) {
    for (int x=0;x<w;x++)
        for (int y=0;y<h;y++)
        {
            auto var_noise = noise.GetNoise((float)x,(float)y);
            auto var_temp = assign_temp(var_noise);
            auto var_hum = assign_hum(var_noise,var_temp);
            auto var_terrain = assign_terrain(var_noise,var_hum,var_temp);
            world_map.emplace(std::tuple(x,y,var_noise),tile(coordinates(x,y,var_noise),var_temp,var_hum,var_terrain));
        }
    return world_map;
}

map::map() {
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
    noise.SetSeed(0);
}

terrain_type map::assign_terrain(float z, float hum, float temp) {
    if (z <= 0) return terrain_type::water;
    if (z > 0) {
        if (hum > 0 && temp > 0) return  terrain_type::grass;
        else return terrain_type::hills;
    }
    return terrain_type::grass;
}


float map::assign_temp(float z)
{
    constants c;
    return c.MaxHeight * z;
}


float map::assign_hum(float z, float temp)
{
    return z + temp;
}