#pragma once

#include <pebble.h>

// Used to turn off logging
#define DEBUG false

// turn this on to test the watch on an emulator
#define DEBUG_VALUES false
#define STEPS_AMNT_INTERVAL 100
#define MAX_STEPS 10000
#define CURRENT_AVERAGE 11000
#define CURRENT_STEPS 50

// Number of days the averaging mechanism takes into account
#define PAST_DAYS_CONSIDERED 7

// Delay after launch before querying the Health API
#define LOAD_DATA_DELAY 500

// customise the goal stroke
#define GFX_PROGRESS_STROKE GColorBlack
#define GFX_GOAL_STROKE GColorWhite

// the offset for the digit display
#define TIME_AND_STEP_CENTER_OFFSET -6

// Time colour
#define COLOR_TIME_DIGITS GColorBlack

// fill thickness of the main progress bar
#define FILL_THICKNESS 11

// the length of the goal line - usually longer than the progress bar
#define FILL_GOAL_LINE 14
