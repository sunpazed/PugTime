#include <pebble.h>
#include "settings.h"
#include "windows/main_window.h"

int theme_bw;
GColor theme_main_bg;
GColor theme_main_time;
void prv_inbox_received_handler();

// Persistent storage key
#define SETTINGS_KEY 926352830


// Initialize the default settings
static void prv_default_settings() {
  settings.theme_main_bg = GColorLightGray;
  settings.theme_main_time = GColorBlack;
  settings.theme_bw = THEME_BW_GREY;
}

// Read settings from persistent storage
static void prv_load_settings() {
  // Load the default settings
  prv_default_settings();
  // Read settings from persistent storage, if they exist
  persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

// Save the settings to persistent storage
static void prv_save_settings() {
  persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
}

void prv_init_settings(void) {

  prv_load_settings();
  // Open AppMessage connection
  app_message_register_inbox_received(prv_inbox_received_handler);
  app_message_open(128, 128);

}

void prv_inbox_received_handler(DictionaryIterator *iter, void *context) {
  
  // Read color preferences
  Tuple *bg_color_t = dict_find(iter, MESSAGE_KEY_theme_main_bg);
  if(bg_color_t) {
    APP_LOG(APP_LOG_LEVEL_INFO, "Color is in Tuple!");
    settings.theme_main_bg = GColorFromHEX(bg_color_t->value->int32);
  } else {
    settings.theme_main_bg = GColorLightGray;//GColorFromHEX(0xAAAAAA);
    APP_LOG(APP_LOG_LEVEL_INFO, "Color is default!");
  }

  Tuple *fg_color_t = dict_find(iter, MESSAGE_KEY_theme_main_time);
  if(fg_color_t) {
    settings.theme_main_time = GColorFromHEX(fg_color_t->value->int32);
  } else {
    settings.theme_main_time = GColorFromHEX(0x000000);    
  }

  Tuple *theme_bw_t = dict_find(iter, MESSAGE_KEY_theme_bw);
  if(theme_bw_t) {
    settings.theme_bw = atoi(theme_bw_t->value->cstring);
  } else {
    settings.theme_bw = THEME_BW_GREY;
  }
  
  APP_LOG(APP_LOG_LEVEL_INFO, "Settings Updated!");
  prv_save_settings();
  main_window_redraw();
  
}


