#pragma once

#include <pebble.h>

#include "data.h"

void graphics_draw_pug(GContext *ctx, GRect bounds, GColor color, GBitmap *bitmap);
void graphics_draw_steps_value(GContext *ctx, GRect bounds);

void graphics_set_window(Window *window);