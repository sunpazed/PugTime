#include "data.h"

    
typedef enum {
  AppKeyCurrentAverage = 0,
  AppKeyDailyAverage,
  AppKeyCurrentSteps
} AppKey;

typedef enum {
  AverageTypeCurrent = 0,
  AverageTypeDaily
} AverageType;

static GBitmap *s_sad_pug, *s_happy_pug;
static GFont s_font_small, s_font_big, s_font_med, s_font_xlrg;

static int s_current_steps, s_daily_average, s_current_average;
static char s_current_steps_buffer[8];
static char s_current_hr_buffer[8];


static void update_average(AverageType type) {
  // Start time is midnight
  const time_t start = time_start_of_today();

  time_t end = start;
  int steps = 0;
  switch(type) {
    case AverageTypeDaily:
      // One whole day
      end = start + SECONDS_PER_DAY;
      if(DEBUG) APP_LOG(APP_LOG_LEVEL_DEBUG, "AverageTypeDaily: %d", end);
    break;
    case AverageTypeCurrent:
      // Time from midnight to now
      end = start + (time(NULL) - time_start_of_today());
      if(DEBUG) APP_LOG(APP_LOG_LEVEL_DEBUG, "AverageTypeCurrent: %d", end);
      break;
    default:
      if(DEBUG) APP_LOG(APP_LOG_LEVEL_ERROR, "Unknown average type!");
      break;
  } 

  // Check the average data is available
  HealthServiceAccessibilityMask mask = health_service_metric_averaged_accessible(
                                HealthMetricStepCount, start, end, HealthServiceTimeScopeWeekly );
  if(mask & HealthServiceAccessibilityMaskAvailable) {
    // Data is available, read it
    steps = (int)health_service_sum_averaged(HealthMetricStepCount, start, end, 
                                                                    HealthServiceTimeScopeWeekly );
    
    if(DEBUG) APP_LOG(APP_LOG_LEVEL_DEBUG, "HealthServiceTimeScopeWeekly is %d", steps);

    if (DEBUG) {
      APP_LOG(APP_LOG_LEVEL_DEBUG, "Step difference is %d", data_get_step_delta());
    }

  // for testing only..
    if (DEBUG_VALUES) {
        steps = MAX_STEPS;
    }
    
  } else {
    if(DEBUG) APP_LOG(APP_LOG_LEVEL_DEBUG, "No data available for daily average");
  }

  // Store the calculated value
  switch(type) {
    case AverageTypeDaily:
      s_daily_average = steps;
      persist_write_int(AppKeyDailyAverage, s_daily_average);

      if(DEBUG) APP_LOG(APP_LOG_LEVEL_DEBUG, "Daily average: %d", s_daily_average);
      break;
    case AverageTypeCurrent:
      s_current_average = steps;
      persist_write_int(AppKeyCurrentAverage, s_current_average);

      // for testing only..
      if (DEBUG_VALUES) {
            //s_current_average = (MAX_STEPS / 15) * 12;
            s_current_average = CURRENT_AVERAGE;
      }
    
      if(DEBUG) APP_LOG(APP_LOG_LEVEL_DEBUG, "Current average: %d", s_current_average);
      break;
    default: break;  // Handled by previous switch
  }
}

void data_update_steps_buffer() {
  int thousands = s_current_steps / 1000;
  int hundreds = s_current_steps % 1000;
  if(thousands > 0) {
    snprintf(s_current_steps_buffer, sizeof(s_current_steps_buffer), "%d%03d", thousands, hundreds);
  } else {
    snprintf(s_current_steps_buffer, sizeof(s_current_steps_buffer), "%d", hundreds);
  }

  main_window_redraw();
}

void data_update_hr_buffer() {
    snprintf(s_current_hr_buffer, sizeof(s_current_hr_buffer), "%d", s_current_hr);  
}

static void load_health_data_handler(void *context) {
  const struct tm *time_now = util_get_tm();

  if (DEBUG_VALUES) {
    s_current_steps = persist_read_int(AppKeyCurrentSteps);
    s_current_steps = s_current_steps + (int)(rand()%STEPS_AMNT_INTERVAL);
    s_current_steps = CURRENT_STEPS;
    s_current_hr = 143;
  } else {
    s_current_steps = health_service_sum_today(HealthMetricStepCount);
  }

  if(DEBUG) APP_LOG(APP_LOG_LEVEL_DEBUG, "Current steps: %d", s_current_steps);
  persist_write_int(AppKeyCurrentSteps, s_current_steps);

  update_average(AverageTypeDaily);
  update_average(AverageTypeCurrent);

  data_update_steps_buffer();
  data_update_hr_buffer();
}

void data_reload_averages() {
  app_timer_register(LOAD_DATA_DELAY, load_health_data_handler, NULL);
}

void data_init() {
  // Load resources
#ifdef PBL_COLOR
  
  #ifdef PBL_PLATFORM_EMERY 
  // Color images
  s_happy_pug = gbitmap_create_with_resource(RESOURCE_ID_PUG_HAPPY_EMERY);
  s_sad_pug = gbitmap_create_with_resource(RESOURCE_ID_PUG_SAD_EMERY);
  #else
  // Color images
  s_happy_pug = gbitmap_create_with_resource(RESOURCE_ID_PUG_HAPPY_PT);
  s_sad_pug = gbitmap_create_with_resource(RESOURCE_ID_PUG_SAD_PT);
  #endif

  
#else
  // BW images
  s_happy_pug = gbitmap_create_with_resource(RESOURCE_ID_PUG_HAPPY_BW);
  s_sad_pug = gbitmap_create_with_resource(RESOURCE_ID_PUG_SAD_BW);
#endif
    
  // changed these fonts to the LECO font
  s_font_small =  fonts_get_system_font(FONT_KEY_LECO_26_BOLD_NUMBERS_AM_PM  );
  //s_font_small =  fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD  );
  s_font_med = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);

  #ifdef PBL_PLATFORM_EMERY 
  s_font_big = fonts_get_system_font(FONT_KEY_LECO_36_BOLD_NUMBERS);
  s_font_xlrg = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_LECO_54));;
  #else
  s_font_big = fonts_get_system_font(FONT_KEY_LECO_36_BOLD_NUMBERS);
  s_font_xlrg = fonts_get_system_font(FONT_KEY_LECO_42_NUMBERS);  
  #endif
  
  
  // First time persist
  if(!persist_exists(AppKeyCurrentSteps)) {
    s_current_steps = 0;
    s_current_average = 0;
    s_daily_average = 0;
  } else {
    s_current_average = persist_read_int(AppKeyCurrentAverage);
    s_daily_average = persist_read_int(AppKeyDailyAverage);
    s_current_steps = persist_read_int(AppKeyCurrentSteps);
  }
  data_update_steps_buffer();

  // Avoid half-second delay loading the app by delaying API read
  data_reload_averages();
}

void data_deinit() {
  gbitmap_destroy(s_happy_pug);
  gbitmap_destroy(s_sad_pug);
}

int data_get_current_steps() {
  return s_current_steps;
}

int data_get_current_average() {
  return s_current_average;
}

int data_get_daily_average() {
  return s_daily_average;
}

void data_set_current_steps(int value) {
  s_current_steps = value;
}

void data_set_current_average(int value) {
  s_current_average = value;
}

void data_set_daily_average(int value) {
  s_daily_average = value;
}

int data_get_step_delta() {
 return data_get_current_steps() - data_get_current_average();
}

GFont data_get_font(FontSize size) {
  switch(size) {
    case FontSizeSmall:  return s_font_small;
    case FontSizeMedium: return s_font_med;
    case FontSizeLarge:  return s_font_big;
    case FontSizeXLarge:  return s_font_xlrg;
    default: return s_font_small;
  }
}

GBitmap* data_get_sad_pug() {
  return s_sad_pug;
}

GBitmap* data_get_happy_pug() {
  return s_happy_pug;
}

char* data_get_current_steps_buffer() {
  return s_current_steps_buffer;
}
