#include "graphics.h"
#include "../settings.h"

#define TOP_RIGHT 72
#define BOT_RIGHT 240
#define BOT_LEFT  384
#define TOP_LEFT  552

#define MULT_X(a, b) (1000 * a / b)
#define DIV_X(a) (a / 1000)
#define MAX(a, b) ((a) > (b) ? a : b)
#define MIN(a, b) ((a) < (b) ? a : b)

#define LINE_CENTER_OFFSET 1

static Window *s_window;


#if defined(PBL_RECT)
static GPoint inset_point(GPoint outer_point, int inset_amount) {
  const GSize display_size = layer_get_bounds(window_get_root_layer(s_window)).size;
  // Insets the given point by the specified amount
  return (GPoint) {
    .x = MAX(inset_amount - 1, MIN(outer_point.x, display_size.w - inset_amount)),
    .y = MAX(inset_amount - 1, MIN(outer_point.y, display_size.h - inset_amount))
  };
}
#endif


void graphics_draw_pug(GContext *ctx, GRect bounds, GColor color, GBitmap *bitmap) {
  GRect shoe_bitmap_box = bounds;
  shoe_bitmap_box.size = gbitmap_get_bounds(data_get_happy_pug()).size;
  const int y_pos = ((bounds.size.h/2) + TIME_AND_STEP_CENTER_OFFSET);        
  
  shoe_bitmap_box.origin.x = (bounds.size.w / 2) - (shoe_bitmap_box.size.w /2);
  shoe_bitmap_box.origin.y = (bounds.size.h / 2) - (shoe_bitmap_box.size.h /4); 

  #ifdef PBL_COLOR
  graphics_context_set_compositing_mode(ctx, GCompOpSet);
  graphics_draw_bitmap_in_rect(ctx, bitmap, shoe_bitmap_box); 
  #else
  graphics_context_set_compositing_mode(ctx, GCompOpSet); // fixed a bug here on Diorite
  graphics_draw_bitmap_in_rect(ctx, bitmap, shoe_bitmap_box); 
  #endif

}

void graphics_draw_steps_value(GContext *ctx, GRect bounds) {
  
  GRect steps_text_box = bounds;
  int current_step_delta = data_get_step_delta();
  char steps_buffer[20];

  snprintf(steps_buffer, sizeof(steps_buffer), "%d", current_step_delta);
    
  const int text_width = graphics_text_layout_get_content_size(steps_buffer, 
      data_get_font(FontSizeSmall), steps_text_box, GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter).w;

  const int text_height = graphics_text_layout_get_content_size(steps_buffer, 
    data_get_font(FontSizeSmall), steps_text_box, GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter).h;

  const int font_padding = text_height / 3;
  
  steps_text_box.size = GSize(text_width, text_height);
  //const int y_pos = 4;        
  
  steps_text_box.origin.x = (bounds.size.w / 2) - (text_width / 2);
  steps_text_box.origin.y = 0;

  // Get total width
  int total_width = 0;

  const int x_margin = ((bounds.size.w) - (text_width + (font_padding*2)))/2;
  const int x_height = PBL_IF_RECT_ELSE(20, 28);
  // const int y_margin = 4;
  const int box_height = text_height;
  const GRect time_rect = grect_inset(bounds, GEdgeInsets(x_height, x_margin, bounds.size.h-box_height-font_padding-x_height, x_margin));

  #ifdef PBL_BW 
  switch(settings.theme_bw){
   case THEME_BW_LIGHT: 
      graphics_context_set_fill_color(ctx, GColorBlack);
      graphics_context_set_text_color(ctx, GColorWhite);
    break; 
   case THEME_BW_GREY: 
      graphics_context_set_fill_color(ctx, GColorWhite);
      graphics_context_set_text_color(ctx, GColorBlack);
    break; 
   case THEME_BW_DARK: 
      graphics_context_set_fill_color(ctx, GColorWhite);
      graphics_context_set_text_color(ctx, GColorBlack);
    break; 
  }
  #endif
  
  #ifdef PBL_COLOR 
    graphics_context_set_fill_color(ctx, settings.theme_main_time);
    graphics_context_set_text_color(ctx, settings.theme_main_bg);
  #endif  
  
  graphics_fill_rect(ctx, time_rect, 6, GCornersAll ); 
  graphics_draw_text(ctx, steps_buffer, data_get_font(FontSizeSmall), 
                     time_rect, GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, NULL);

}

void graphics_set_window(Window *window) {
  s_window = window;
}
