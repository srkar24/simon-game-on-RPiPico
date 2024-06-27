#include "debounce.hpp"
#include "simon_game.hpp"
#include <cstdint>
#include <iostream>

extern CurrentBtnState_t SimonGame::current_btn_stat;

void SimonGame::gpio_callback(uint gpio, uint32_t events) {
    SimonGame::current_btn_stat = {static_cast<int32_t>(gpio), events, true};
}