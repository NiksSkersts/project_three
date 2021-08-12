#include <cstdlib>
#include <raylib.h>
#include <vector>
#include "button.h"
class game_ui {

public:
    game_ui();
    std::vector<button> button_storage;
};