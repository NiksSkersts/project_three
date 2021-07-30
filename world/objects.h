#include "../basics/coordinates.h"
#include "object_type.h"
class map_object
{
    public:  
    map_object(float x, float y, float z, object_type obj);
    coordinates coords;
    object_type objectType;
};