#pragma once
#include "terrain_type.h"
#include "../basics/coordinates.h"
#include <vector>
struct tile
{
public:
    //inits a single tile unit.
    tile(struct coordinates coords, float temp, float hum, terrain_type type) : coords(coords),terrainType(type),humidity(hum),temperature(temp){};
	struct coordinates coords;
    terrain_type terrainType;
	float humidity;
	float temperature;
};

