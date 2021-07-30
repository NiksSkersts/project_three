#include "objects.h"
map_object::map_object(float x, float y,float z, object_type obj)
{
    coords.x = x;
    coords.y = y;
    coords.z = z;
    objectType = obj;
}