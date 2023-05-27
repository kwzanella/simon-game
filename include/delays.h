#pragma once

// all delays below are given in ms (millisecond)

#define USER_GAME_DELAY 300  // time between user interaction (button press) and game playing previous actions
#define STARTUP_DELAY   350  // amount of time for a single tone to play in startup
#define ACTION_DELAY    250  // time between blinks and tones plays
#define INCORRECT_DELAY 500  // amount of time for a single tone to play when incorrect button press
#define RESTART_DELAY   1000 // time between playing the incorrect button press sound and restarting the game
#define START_DELAY     400  // time between startup and game picking random button
