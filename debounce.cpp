#include "debounce.hpp"

#include <cstdio>

/**
* @brief Check if the button state has been stable for a sufficient amount of
* time.
*
* @param prev_time The previous time stamp.
* @param curr_time The current time stamp.
* @return true if the button state has been stable for a sufficient amount of
* time, false otherwise.
*/
bool is_stable(const absolute_time_t prev_time, const absolute_time_t curr_time) {
    if (curr_time < prev_time) {
        return false;
    }

    if (curr_time > prev_time) {
        return (int64_t)(curr_time - prev_time) > DEBOUNCE_DELAY;
    }

    return false;
}


/**
* @brief Check if the button state has changed.
*
* @param prev_state The previous state of the button.
* @param curr_state The current state of the button.
* @return true if the button state has changed, false otherwise.
*/
bool has_changed(bool prev_state, bool curr_state) {
  bool changed = (prev_state ^ curr_state);
  return changed;
}


/**
* @brief Check if the button state has changed and has been stable for a
* sufficient amount of time.
* @param btn The button state to be checked.
* @return true if the button state has changed and has been stable for a
* sufficient amount of time, false otherwise.
*/
bool debounce(const volatile BtnState &btn) {
  if (has_changed(btn.prev_state, btn.curr_state)) {
    if (is_stable(btn.prev_time, btn.curr_time)) {
      return true;
    }
  }
  return false;
}


/**
* @brief Set the button state to indicate a rising edge.
*
* @param btn The button state to be updated.
*/
void set_rising_edge_state(volatile BtnState *btn) {
  btn->prev_state = 0;
  btn->curr_state = 1;
  btn->prev_time = get_absolute_time();
  btn->curr_time = 0;
}


/**
* @brief Set the button state to indicate a falling edge.
*
* @param btn The button state to be updated.
*/
void set_falling_edge_state(volatile BtnState *btn) {
  btn->prev_state = 1;
  btn->curr_state = 0;
  btn->curr_time = get_absolute_time();
}


/**
* @brief Reset the button state.
*
* @param btn The button state to be reset.
*/
void reset_btn_state(volatile BtnState *btn) {
  btn->prev_state = 0;
  btn->curr_state = 0;
  btn->prev_time = 0;
  btn->curr_time = 0;
}

/**
* @brief Update the button state.
*
* @param btn The button state to be updated.
*/
void update_btn_state(volatile BtnState *btn) {
  btn->prev_state = btn->curr_state;
  btn->curr_state = gpio_get(btn->but_pin);
}


/**
* @brief Update the button time stamps.
*
* @param btn The button state whose time stamps are to be updated.
*/
void update_btn_time(volatile BtnState *btn) {
  btn->prev_time = btn->curr_time;
  btn->curr_time = get_absolute_time();
}