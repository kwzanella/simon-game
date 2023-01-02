#include <Arduino.h>

#define R_BUTTON 10  // red button pin
#define Y_BUTTON 9   // yellow button pin
#define B_BUTTON 8   // blue button pin
#define G_BUTTON 7   // green button pin

#define R_LED 6  // red led pin
#define Y_LED 5  // yellow led pin
#define B_LED 4  // blue led pin
#define G_LED 3  // green led pin

#define BUZZER 2  // buzzer pin

#define R_TONE 195.998  // G3 -- https://en.wikipedia.org/wiki/G_(musical_note)
#define Y_TONE 261.626  // C4 -- https://en.wikipedia.org/wiki/C_(musical_note)
#define B_TONE 329.628  // E4 -- https://en.wikipedia.org/wiki/E_(musical_note)
#define G_TONE 391.995  // G4 -- https://en.wikipedia.org/wiki/G_(musical_note)

#define USER_GAME_DELAY 300  // time between user interaction (pressing buttons) and game playing previous actions
#define STARTUP_DELAY 350    // amount of time for a single tone to play in startup
#define ACTION_DELAY 250     // time between blinks and tones plays
#define INCORRECT_DELAY 500  // amount of time for a single tone to play when incorrect button press
#define RESTART_DELAY 1000   // time between playing the incorrect button press sound and restarting the game
#define START_DELAY 400      // time between startup and game picking random button
#define DEBOUNCE_TIME 75     // debounce time to avoid input noise

#define MAX_ACTIONS 100
#define NUM_BUTTONS 4

struct button {
    unsigned short button;  // button pin
    unsigned short led;  // led pin
    double m_tone;  // musical tone
};

unsigned short action = 0;  // controls previous_actions indexing
button* pressed = NULL;      // controls pressed button
bool is_correct = false;    // controls if button pressed is correct

button** previous_actions = new button*[MAX_ACTIONS];  // stores adress of previously pressed buttons in heap
button buttons[4] = {
    (button){R_BUTTON, R_LED, R_TONE},  // red
    (button){Y_BUTTON, Y_LED, Y_TONE},  // yellow
    (button){B_BUTTON, B_LED, B_TONE},  // blue
    (button){G_BUTTON, G_LED, G_TONE}   // green
};  // stores available buttons

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

void blink(int led_pin) {
    digitalWrite(led_pin, HIGH);
    delay(ACTION_DELAY);

    digitalWrite(led_pin, LOW);
}

button* wait_button_press() {
    while(1) {
        for(int button=0; button < NUM_BUTTONS; button++) {
            if (digitalRead(buttons[button].button) == LOW) {
                delay(DEBOUNCE_TIME);
                return &buttons[button];
            }
        }
    }
}

// play previous actions
void simon_previous() {
    for(unsigned short i=0; i <= action; i++) {
        blink(previous_actions[i]->led);
        play_tone(previous_actions[i]->m_tone);
    }
}

// choose next action
void simon_next() {
    randomSeed(analogRead(0));  // needed for better working of random()
    previous_actions[action] = &buttons[random(0, NUM_BUTTONS)];  // store variable adress

    simon_previous();  // plays previous actions
    action++;
}

void simon_start() {
    startup_sound();
    delay(START_DELAY);
    simon_next();
}

// reset array and variables and start the game
void simon_restart() {
    delete[] previous_actions;
    previous_actions = new button*[MAX_ACTIONS];

    action = 0;
    pressed = NULL;
    is_correct = false;
    
    simon_start();
}

// simon game main function
void simon_game() {
    if (action == MAX_ACTIONS - 1) {  // cannot go further
        delete[] previous_actions;
        previous_actions = NULL;
        exit(0);
    }

    for(unsigned short i=0; i < action; i++) {  // checks if user presses correct sequence of buttons
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
        simon_next();
    }
    else {  // only gets here if one button is pressed incorrectly
        delay(USER_GAME_DELAY);
        incorrect_press_sound();
        delay(RESTART_DELAY);
        simon_restart();
    }
}

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

    simon_start();
}

void loop() {
    simon_game();
}