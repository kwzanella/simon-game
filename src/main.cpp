#include <Arduino.h>
#include "simon.hpp"
#include "pins.h"
#include "tones.h"
#include "button.h"

button buttons[4] = {
    (button){R_BUTTON, R_LED, R_TONE},  // red
    (button){Y_BUTTON, Y_LED, Y_TONE},  // yellow
    (button){B_BUTTON, B_LED, B_TONE},  // blue
    (button){G_BUTTON, G_LED, G_TONE}   // green
};

SimonGame simon(buttons);

void setup() {
    pinMode(R_LED, OUTPUT);
    pinMode(Y_LED, OUTPUT);
    pinMode(B_LED, OUTPUT);
    pinMode(G_LED, OUTPUT);

    pinMode(R_BUTTON, INPUT_PULLUP);
    pinMode(Y_BUTTON, INPUT_PULLUP);
    pinMode(B_BUTTON, INPUT_PULLUP);
    pinMode(G_BUTTON, INPUT_PULLUP);

    pinMode(BUZZER, OUTPUT);

    simon.start();
}

void loop() {
    simon.game();
}