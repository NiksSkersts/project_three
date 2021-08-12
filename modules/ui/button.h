#include "button_type.h"
#include <raylib.h>
#include <sys/types.h>

class button{
public:
    button(int id, button_type btn,Vector2 loc,int size){
        this->id=id;
        //ident for filtering the correct button;
        this->buttonType=btn;
        //location offset;
        this->location=loc;
        this->size=size;
        this->dirty = false;
    }
    //dirty ==true => event has happened that requires prog to wait for click;
    bool dirty;
    uint id;
    button_type buttonType;
    Vector2 location;
    int size;
};
