#include "game_ui.h"

game_ui::game_ui() {
    button button_build(1,button_type::button_build,{10,-32},32);

    button_storage.push_back(button_build);
}
