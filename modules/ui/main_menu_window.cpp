#include "main_menu_window.h"
using namespace ui;
main_menu_window::main_menu_window() {
    Vector2 mouse_position{0,0};
    while (this->menu){
        mouse_position = GetMousePosition();
        ClearBackground(WHITE);
        BeginDrawing();
        DrawFPS(10,10);
        switch(code) {
            case main:
                DrawTextRec(GetFontDefault(),button_start.text,button_start.button_rectangle,button_start.font_size,1.0f,false,function_detect_mouse_over(button_start,mouse_position));
                DrawTextRec(GetFontDefault(),button_options.text,button_options.button_rectangle,button_options.font_size,1.0f,false,function_detect_mouse_over(button_options,mouse_position));
                DrawTextRec(GetFontDefault(),button_credits.text,button_credits.button_rectangle,button_credits.font_size,1.0f,false,function_detect_mouse_over(button_credits,mouse_position));
                DrawTextRec(GetFontDefault(),button_quit.text,button_quit.button_rectangle,button_quit.font_size,1.0f,false,function_detect_mouse_over(button_quit,mouse_position));
                break;
            case options:
                break;
            case credits:
                break;
            case begin_game:
                break;
            case quit:
                break;
        }
        EndDrawing();
    }
}

Color main_menu_window::function_detect_mouse_over(button &button,const Vector2 mouse_position) {
    if (CheckCollisionPointRec(mouse_position,button.button_rectangle))
    {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            return BLUE;
        return RED;
    }
    return BLACK;
}