#pragma once

#define R_BUTTON 10 // red button pin
#define Y_BUTTON 9  // yellow button pin
#define B_BUTTON 8  // blue button pin
#define G_BUTTON 7  // green button pin

#define R_LED 6  // red led pin
#define Y_LED 5  // yellow led pin
#define B_LED 4  // blue led pin
#define G_LED 3  // green led pin

#define BUZZER 2  // buzzer pin

#define R_TONE 195.998  // G3 -- https://en.wikipedia.org/wiki/G_(musical_note)
#define Y_TONE 261.626  // C4 -- https://en.wikipedia.org/wiki/C_(musical_note)
#define B_TONE 329.628  // E4 -- https://en.wikipedia.org/wiki/E_(musical_note)
#define G_TONE 391.995  // G4 -- https://en.wikipedia.org/wiki/G_(musical_note)

#define USER_GAME_DELAY 300  // time between user interaction (button press) and game playing previous actions
#define STARTUP_DELAY   350  // amount of time for a single tone to play in startup
#define ACTION_DELAY    250  // time between blinks and tones plays
#define INCORRECT_DELAY 500  // amount of time for a single tone to play when incorrect button press
#define RESTART_DELAY   1000 // time between playing the incorrect button press sound and restarting the game
#define START_DELAY     400  // time between startup and game picking random button
#define DEBOUNCE_TIME   75   // debounce time to avoid input noise

#define MAX_ACTIONS 100
#define NUM_BUTTONS 4

struct button {
    unsigned short button;  // button pin
    unsigned short led;  // led pin
    double m_tone;  // musical tone
};
