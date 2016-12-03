#include <pebble.h>

#include "modules/data.h"
#include "modules/health.h"
#include "modules/util.h"

#include "windows/main_window.h"
#include <pebble-events/pebble-events.h>
#include "settings.h"

static void tick_handler(struct tm *tick_time, TimeUnits changed) {
  main_window_update_time(tick_time);
  data_reload_averages();
  main_window_redraw();
}

void init() {
  
  data_init();
  health_init();
  main_window_push();

  if (DEBUG_VALUES) {
    tick_timer_service_subscribe(SECOND_UNIT, tick_handler); // updated from SECOND_UNIT to MINUTE_UNIT to save battery 
  } else {
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler); // updated from SECOND_UNIT to MINUTE_UNIT to save battery       
  }
  
  main_window_update_time(util_get_tm());
  prv_init_settings();

}

void deinit() { 
}

int main() {
  init();
  app_event_loop();
  deinit();
}
