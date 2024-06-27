#ifndef __SIMON_GAME__
#define __SIMON_GAME__

#include "pico/stdlib.h"
#include "debounce.hpp"
#include <iostream>
#include <vector>

namespace SimonGame {
    static const uint32_t BLINK_LED_DELAY = 500;
    static const uint8_t ONBOARD_LED = 25;  // Heartbeat
    static const uint8_t LED0 = 12;
    static const uint8_t LED1 = 13;
    static const uint8_t LED2 = 14;
    static const uint8_t LED3 = 15;
    static const uint8_t BTN0 = 16;
    static const uint8_t BTN1 = 17;
    static const uint8_t BTN2 = 18;
    static const uint8_t BTN3 = 19;
    static const uint8_t BTN4 = 20; // RESET
    static const uint8_t PATTERN_LEN = 10;
    static const uint8_t NUMBER_OF_BTNS = 5;
    extern CurrentBtnState_t current_btn_stat;
    void core1_entry();
    void gpio_callback(uint gpio, uint32_t events);

    class SimonGameClass {
        public:
            SimonGameClass();
            void initialize_gpio();
            void initialize_irq();
            void check_user_input();
            void check_pattern_gen();
            void generate_pattern();
            void show_pattern();
            bool is_game_over();
            void reset_game();
            uint32_t get_random_num();

            volatile bool waiting_for_pattern;
            int level;
            int user_input_number;
            int game_over;
            int user_point;
            volatile BtnState btns[NUMBER_OF_BTNS];
            // int rand_pattern[10]
            std::vector<int> rand_pattern;
    };
};

#endif