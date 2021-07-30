#include "tile.h"
#include "../basics/constants.h"
#include "../utils/FastNoiseLite.h"

//inits a single tile unit.
tile::tile(int x, int y) {
    this->coords = coordinates();
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
    noise.SetSeed(0);
    coords.x = x;
    coords.y = y;
    coords.z = noise.GetNoise(coords.x, coords.y);
    this->temperature = assign_temp(coords.z);
    this->humidity = assign_hum(coords.z, temperature);
    this->terrainType = assign_terrain(coords.z, humidity, temperature);
}
terrain_type tile::assign_terrain(float z, float hum, float temp) {
    if (z <= 0) return terrain_type::water;
    if (z > 0) {
        if (hum > 0 && temp > 0) return  terrain_type::grass;
        else return terrain_type::hills;
    }
    return terrain_type::grass;
}


float tile::assign_temp(float z)
{
    // TODO: Add your implementation code here.
    constants c;
    return c.MaxHeight * z;
}


float tile::assign_hum(float z, float temp)
{
    // TODO: Add your implementation code here.
    return z + temp;
}
