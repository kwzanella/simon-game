#include <Arduino.h>

#include "simon.hpp"
#include "helpers.h"
#include "delays.h"
#include "button.h"

SimonGame::SimonGame(button* buttons) :
    previous_actions(new button* [MAX_ACTIONS]),
    action(0),
    pressed(nullptr),
    is_correct(false),
    buttons(buttons)
{}

SimonGame::~SimonGame() {
    this->reset();
}

void SimonGame::reset() {
    delete[] previous_actions;
    action = 0;
    pressed = NULL;
    is_correct = false;
}

button* SimonGame::wait_button_press() {
    while(1) {
        for(uint8_t button=0; button < NUM_BUTTONS; ++button) {
            if (digitalRead(buttons[button].button) == LOW) {
                delay(DEBOUNCE_TIME);
                return &buttons[button];
            }
        }
    }
}

void SimonGame::play_next_action() {
    randomSeed(analogRead(0));  // needed for better working of random()
    previous_actions[action] = &buttons[random(0, NUM_BUTTONS)];  // store variable adress

    this->play_previous_actions();  // plays previous actions
    ++action;
}

void SimonGame::play_previous_actions() {
    for(uint8_t i=0; i <= action; ++i) {
        blink(previous_actions[i]->led);
        play_tone(previous_actions[i]->m_tone);
    }
}

void SimonGame::start() {
    startup_sound();
    delay(START_DELAY);
    this->play_next_action();
}

void SimonGame::restart() {
    this->reset();
    this->previous_actions = new button* [MAX_ACTIONS];
    
    this->start();
}

void SimonGame::game() {
    if (action == MAX_ACTIONS - 1) {  // cannot go further
        exit(0);
    }

    for(uint8_t i=0; i < action; ++i) {  // checks if user presses correct sequence of buttons
        pressed = wait_button_press();
        
        blink(pressed->led);
        play_tone(pressed->m_tone);

        if (pressed->button == previous_actions[i]->button) {
            is_correct = true;  // if button is pressed correctly, set flag to true
        }
        else {
            is_correct = false;  // if button is pressed incorrectly, set flag to false and break out of loop
        break;
        }
    }

    if (is_correct) {  // only gets here if all buttons are pressed correctly
        delay(USER_GAME_DELAY);
        this->play_next_action();
    }
    else {  // only gets here if one button is pressed incorrectly
        delay(USER_GAME_DELAY);
        incorrect_press_sound();
        delay(RESTART_DELAY);
        this->restart();
    }
}