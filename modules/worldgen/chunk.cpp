#include <basics/constants.h>
#include <utils/FastNoiseLite.h>
#include "chunk.h"
constants con;
chunk::chunk(Vector2 startingCoordinates) : starting_coordinates(startingCoordinates) {
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
    noise.SetSeed(con.seed);
    for (int x=0;x<con.chunksize;x++)
        for (int y=0;y<con.chunksize;y++)
        {
            auto var_noise = noise.GetNoise((float)x,(float)y);
            Vector3 coords = (Vector3) {roundevenf(startingCoordinates.x)+x, roundevenf(startingCoordinates.y)+y,var_noise};
            auto var_temp = assign_temp(var_noise);
            auto var_hum = assign_hum(var_noise,var_temp);
            auto var_terrain = assign_terrain(var_noise,var_hum,var_temp);
            chunk_array.emplace(
                    std::tuple(coords.x,coords.y),
                    tile(coords,var_terrain,var_hum,var_temp)
                    );
        }
}
terrain_type chunk::assign_terrain(float z, float hum, float temp) {
    if (z <= 0) return terrain_type::water;
    if (z > 0) {
        if (hum > 0 && temp > 0) return  terrain_type::grass;
        else return terrain_type::hills;
    }
    if (z<0) return terrain_type::water;
    return terrain_type::grass;
}
float chunk::assign_temp(float z)
{
    return cosf(z);
}
float chunk::assign_hum(float z, float temp)
{
    return ((temp*z+1)/(2));
}
