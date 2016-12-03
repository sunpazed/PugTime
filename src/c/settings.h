#pragma once

#define THEME_BW_GREY 0
#define THEME_BW_LIGHT 1
#define THEME_BW_DARK 2

GColor theme_main_bg;
GColor theme_main_time;
int theme_bw;
void prv_init_settings();

// Define our settings struct
typedef struct ClaySettings {
  GColor theme_main_bg;
  GColor theme_main_time;
  int theme_bw;
} ClaySettings;

// An instance of the struct
ClaySettings settings;