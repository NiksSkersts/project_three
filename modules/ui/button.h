#include <raylib.h>
namespace ui{
    class button{
    public:
        enum button_type{
            main_menu,
            game
        };
        //construct a button in runtime
        button(int id, button_type btn, const char* text, Vector2 loc){
            this->id=id;
            this->text = text;
            //ident for filtering the correct button;
            this->buttonType=btn;
            //location offset;
            this->location=loc;
            this->button_rectangle = {location.x,location.y,(float)MeasureText(text,this->font_size),this->font_size};
            this->selected = false;
        }
        ~button(){
            //todo test this, probably doesn't even work.
            delete this;
        }
        const char* text;
        int id;
        button_type buttonType;
        Vector2 location;
        Rectangle button_rectangle;
        //30pt == 40px
        float font_size{30};
        bool selected{false};
    };
}
