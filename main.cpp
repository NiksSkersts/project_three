#include "modules/ui/main_menu_window.h"
int main()
{
    InitWindow(1000, 1000, "project_two");
    auto menu = ui::main_menu_window();
    return 0;
}
