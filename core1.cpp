#include "simon_game.hpp"
#include "pico/multicore.h"

void SimonGame::core1_entry() {
    while(1) {
        gpio_put(SimonGame::ONBOARD_LED, 1);
        sleep_ms(SimonGame::BLINK_LED_DELAY);
        gpio_put(SimonGame::ONBOARD_LED, 0);
        sleep_ms(SimonGame::BLINK_LED_DELAY);
    }
}