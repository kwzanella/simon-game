#include <Arduino.h>

#include "helpers.h"
#include "tones.h"
#include "pins.h"
#include "delays.h"

void startup_sound() {
    tone(BUZZER, R_TONE);
    delay(STARTUP_DELAY);

    tone(BUZZER, Y_TONE);
    delay(STARTUP_DELAY);

    tone(BUZZER, B_TONE);
    delay(STARTUP_DELAY);

    tone(BUZZER, G_TONE);
    delay(STARTUP_DELAY);

    noTone(BUZZER);  // buzzer continues to play without this
}

void incorrect_press_sound() {
    tone(BUZZER, R_TONE);
    delay(INCORRECT_DELAY);

    tone(BUZZER, Y_TONE);
    delay(INCORRECT_DELAY);

    tone(BUZZER, R_TONE);
    delay(INCORRECT_DELAY);

    noTone(BUZZER);
}

void play_tone(double t) {
    tone(BUZZER, t);
    delay(ACTION_DELAY);
    noTone(BUZZER);
}

void blink(uint8_t led_pin) {
    digitalWrite(led_pin, HIGH);
    delay(ACTION_DELAY);

    digitalWrite(led_pin, LOW);
}
