#pragma once
#include "terrain_type.h"
#include "coordinates.h"
#include <vector>
class tile
{
public:
	tile(int x, int y);
	coordinates coords;
	terrain_type terrainType;
	float humidity;
	float temperature;
	terrain_type assign_terrain(float z, float hum, float temp);
	float assign_temp(float z);
	float assign_hum(float z, float temp);
};

