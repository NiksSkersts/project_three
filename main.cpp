#include "modules/ui/AppInit.h"
#include "modules/ui/main_menu_window.h"
int main()
{
    InitWindow(1000, 1000, "project_two");
    auto menu = ui::main_menu_window();
    auto game = ui::AppInit();
    return 0;
}
