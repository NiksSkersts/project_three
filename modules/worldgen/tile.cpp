#include "tile.h"
worldgen::tile::tile(Vector3 coords, terrain_type t_type, float hum, float temp,object_type obj_type) {
    this->coordinates = coords;
    this->temperature = temp;
    this->humidity = hum;
    this->type = t_type;
    this->obj = obj_type;
}
worldgen::tile::tile(Vector2 coords, bool) {
    this->coordinates = {coords.x,coords.y,0};
    this->type = terrain_type::border;
}
worldgen::tile::tile(Vector2 coords) {
    function_init_noise_settings();
    this->coordinates = {coords.x,coords.y,assign_height(coords)};
    this->temperature = assign_temp(this->coordinates.z);
    this->humidity = assign_hum(this->coordinates.z, this->temperature);
    this->type = assign_terrain(this->coordinates.z, this->humidity, this->temperature);
    this->obj = assign_obj(this->type);
}
worldgen::tile::~tile() {
}
void worldgen::tile::function_init_noise_settings() {
    // init noise settings;
}
float worldgen::tile::assign_height(Vector2 coords){
    //sec_check if var noise ! x>= -1  AND !x <= 1 : Do it again. [Shouldn't happen];
    sec_check:
    float var_noise = this->noise.GetNoise((float)coords.x,(float)coords.y);
    if ((var_noise>=-1 && var_noise <=1)!= true) goto sec_check;
    return var_noise;
}
worldgen::tile::terrain_type worldgen::tile::assign_terrain(float z, float hum, float temp) {
    if (z <= 0) return terrain_type::water;
    if (hum > 0 && temp > 0 && z < 0.5) return  terrain_type::grass;
    if(z >= 0.5) return terrain_type::hills;
    return terrain_type::grass;
}
float worldgen::tile::assign_temp(float z)
{
    return cosf(z);
}
float worldgen::tile::assign_hum(float z, float temp)
{
    return ((temp*z+1)/(2));
}
worldgen::tile::object_type worldgen::tile::assign_obj(terrain_type var_terrain)
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
