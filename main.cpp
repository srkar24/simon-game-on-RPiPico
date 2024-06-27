#include<cstdlib>
#include "pico/multicore.h"
#include "simon_game.hpp"

int main(void) {
    SimonGame::SimonGameClass game_obj;
    game_obj.initialize_gpio();
    game_obj.initialize_irq();
    multicore_launch_core1(SimonGame::core1_entry);
    while (1) {
        game_obj.check_user_input();
        if (game_obj.is_game_over()) {
            continue;
        }
        game_obj.check_pattern_gen();
    }
}