#include <modules/AppInit.h>
#include <basics/constants.h>
#include "raylib.h"
int main()
{
    constants con;
    AppInit app(con.screensize,con.screensize);
    return 0;
}
