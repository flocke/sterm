#ifndef _STERM_CONFIGURATION_H
#define _STERM_CONFIGURATION_H

#include <vte/vte.h>

typedef struct {
  GdkColor foreground;
  GdkColor background;
  GdkColor *colors;
  int palette_size;
  gchar *font;
  VteTerminalCursorBlinkMode cursor_blink;
  VteTerminalCursorShape cursor_shape;
  glong scrollback_lines;
} STermConfig;

STermConfig* new_default_config ();
STermConfig* parse_config_file ( gchar *config_file );

#endif
