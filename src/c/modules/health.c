#include "health.h"

static void health_handler(HealthEventType event, void *context) {
  data_set_current_steps((int)health_service_sum_today(HealthMetricStepCount));
  data_update_steps_buffer();
}

void health_init() {
  health_service_events_subscribe(health_handler, NULL);
}
