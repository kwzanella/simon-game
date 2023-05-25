#pragma once

#include "button.h"

#define NUM_BUTTONS 4
#define MAX_ACTIONS 100
#define DEBOUNCE_TIME   75  // debounce time to avoid input noise

class SimonGame {
private:
    button** previous_actions;  // stores address of previously pressed buttons
    uint8_t action;             // controls the indexing of previous_actions
    button* pressed;            // controls pressed button
    bool is_correct;            // controls if button pressed is corrrect
    button* buttons;            // available buttons

    button* wait_button_press();
    void play_previous_actions();
    void play_next_action();

public:
    SimonGame(button* buttons);
    ~SimonGame();

    void start();
    void restart();
    void game();
};