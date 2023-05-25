#pragma once

#include "button.h"

void startup_sound();
void incorrect_press_sound();
void play_tone(double t);
void blink(uint8_t led_pin);
button* wait_button_press();