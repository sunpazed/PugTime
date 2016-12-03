#include "main_window.h"
#include <pebble-events/pebble-events.h>
#include "../settings.h"

static Window *s_window;
static Layer *s_canvas_layer, *s_text_layer, *s_steps_layer;

static char s_current_time_buffer[8];

static void progress_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  const int fill_thickness = PBL_IF_RECT_ELSE(FILL_THICKNESS, (180 - grect_inset(bounds, GEdgeInsets(FILL_THICKNESS)).size.h) / 2);
  int current_steps = data_get_current_steps();
  int daily_average = data_get_daily_average();
  int current_average = data_get_current_average();

  // Set new exceeded daily average
  if(current_steps > daily_average) {
    daily_average = current_steps;
    data_set_daily_average(daily_average);
  }

  // Decide color scheme based on progress to/past goal
  GColor scheme_color;
  GBitmap *bitmap;
  if(current_steps >= current_average) {
    scheme_color  = GColorJaegerGreen;
    bitmap = data_get_happy_pug();
  } else {
    scheme_color = GColorVividCerulean;
    bitmap = data_get_sad_pug();
  }

  #ifdef PBL_BW 
  switch(settings.theme_bw){
   case THEME_BW_LIGHT: 
    graphics_context_set_fill_color(ctx, GColorWhite);
    break; 
   case THEME_BW_GREY: 
    graphics_context_set_fill_color(ctx, GColorLightGray);
    break; 
   case THEME_BW_DARK: 
    graphics_context_set_fill_color(ctx, GColorBlack);
    break; 
  }
  #endif
  
  #ifdef PBL_COLOR
    graphics_context_set_fill_color(ctx, settings.theme_main_bg);
  #endif
    
  graphics_fill_rect(ctx, GRect(0, 0, bounds.size.w, bounds.size.h), 0, GCornerNone);
  graphics_draw_pug(ctx, bounds, scheme_color, bitmap);
  
}

static void steps_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  graphics_draw_steps_value(ctx, bounds);
}

static void text_update_proc(Layer *layer, GContext *ctx) {
  const GRect layer_bounds = layer_get_bounds(layer);

  #ifdef PBL_PLATFORM_EMERY
  const GFont font_large = data_get_font(FontSizeXLarge);
  #else
  const GFont font_large = data_get_font(FontSizeLarge);
  #endif

  // Get total width
  int total_width = 0;
  GSize time_size = graphics_text_layout_get_content_size(
    s_current_time_buffer, font_large, layer_bounds, GTextOverflowModeWordWrap, GTextAlignmentLeft);
  total_width += time_size.w;

  const int x_margin = (layer_bounds.size.w - total_width) / 4;
  #ifdef PBL_PLATFORM_EMERY
  const int y_margin = 4;
  #else
  const int y_margin = PBL_IF_RECT_ELSE(8, 2);
  #endif
  const GRect time_rect = grect_inset(layer_bounds, GEdgeInsets(-y_margin, x_margin, x_margin, x_margin));


  #ifdef PBL_BW 
  switch(settings.theme_bw){
   case THEME_BW_LIGHT: 
      graphics_context_set_text_color(ctx, GColorBlack);
    break; 
   case THEME_BW_GREY: 
      graphics_context_set_text_color(ctx, GColorBlack);
    break; 
   case THEME_BW_DARK: 
      graphics_context_set_text_color(ctx, GColorWhite);
    break; 
  }
  #endif
  
  #ifdef PBL_COLOR 
    graphics_context_set_text_color(ctx, settings.theme_main_time);
  #endif
  
  graphics_draw_text(ctx, s_current_time_buffer, font_large, time_rect, 
                     GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);

  if(!clock_is_24h_style()) {
    // 12 hour mode
    const struct tm *time_now = util_get_tm();
    const bool am = time_now->tm_hour < 12;
    const int spacing = 2;

  }
}


static void display_time_layer() {
    layer_set_hidden(s_text_layer, false);
    layer_set_hidden(s_steps_layer, true);  
}

static void accel_tap_handler(AccelAxisType axis, int32_t direction) {
    // A tap event occured
    if(DEBUG) APP_LOG(APP_LOG_LEVEL_DEBUG, "We got a tap: %d", direction);
    layer_set_hidden(s_text_layer, true);
    layer_set_hidden(s_steps_layer, false);
    app_timer_register(3000, display_time_layer, NULL);
}


/*********************************** Window ***********************************/

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  s_canvas_layer = layer_create(window_bounds);
  layer_set_update_proc(s_canvas_layer, progress_update_proc);
  layer_add_child(window_layer, s_canvas_layer);

  #ifdef PBL_PLATFORM_EMERY
  static int offset = 18;
  #else
  static int offset = 0;
  #endif

  s_steps_layer = layer_create(window_bounds);
  layer_set_update_proc(s_steps_layer, steps_update_proc);
  layer_add_child(window_layer, s_steps_layer);
  layer_set_hidden(s_steps_layer, true);  

  //display_time_layer();
    
  GEdgeInsets time_insets = GEdgeInsets((window_bounds.size.h/6) + TIME_AND_STEP_CENTER_OFFSET - offset, 0, 0, 0);
  s_text_layer = layer_create(grect_inset(window_bounds, time_insets));
  layer_set_update_proc(s_text_layer, text_update_proc);
  layer_add_child(window_layer, s_text_layer);
  
  // Subscribe to tap events
  accel_tap_service_subscribe(accel_tap_handler);

}

static void window_unload(Window *window) {
  layer_destroy(s_canvas_layer);
  layer_destroy(s_text_layer);

  window_destroy(s_window);
}

void main_window_push() {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_window, true);

  graphics_set_window(s_window);
}

void main_window_update_time(struct tm* tick_time) {
  strftime(s_current_time_buffer, sizeof(s_current_time_buffer),
    clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);
  layer_mark_dirty(s_text_layer);
  layer_mark_dirty(s_steps_layer);
}

void main_window_redraw() {
  if(s_canvas_layer && s_text_layer) {
    layer_mark_dirty(s_canvas_layer);
    layer_mark_dirty(s_text_layer);
    layer_mark_dirty(s_steps_layer);
  }
}
