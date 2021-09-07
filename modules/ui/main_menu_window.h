#include "button.h"
#include <vector>
namespace ui{
    class main_menu_window {
    public:
        enum window_code {
            main,
            options,
            credits,
            begin_game,
            quit
        };
        bool menu {true};
        window_code code {window_code::main};
        button button_start {0,button::main_menu,"Start",{(float)(GetScreenWidth()/2)-(MeasureText("Start",30)/2), (float)(GetScreenHeight()/2)-50}};
        button button_options {0,button::main_menu,"Options",{(float)(GetScreenWidth()/2)-(MeasureText("Options",30)/2), (float)(GetScreenHeight()/2)}};
        button button_credits {0,button::main_menu,"Credits",{(float)(GetScreenWidth()/2)-(MeasureText("Credits",30)/2), (float)(GetScreenHeight()/2)+50}};
        button button_quit {0,button::main_menu,"Quit",{(float)(GetScreenWidth()/2)-(MeasureText("Quit",30)/2), (float)(GetScreenHeight()/2)+100}};
        main_menu_window();

        Color function_detect_mouse_over(button &button, Vector2 mouse_position);
    };
}
