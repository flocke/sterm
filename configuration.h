/*
  This file is part of STerm.

  STerm is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  STerm is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with STerm.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _STERM_CONFIGURATION_H
#define _STERM_CONFIGURATION_H

#include <vte/vte.h>

typedef struct {
  GdkModifierType modifier;
  guint keyval;
  gchar *func;
} STermKeySym;

typedef struct {
  glong scrollback_lines;
  gboolean allow_bold;
  gboolean visible_bell;
  gboolean audible_bell;
  gboolean scroll_on_keystroke;
  gboolean scroll_on_output;
  gboolean rewrap_on_resize;
  gboolean mouse_autohide;

  VteTerminalCursorBlinkMode cursor_blink;
  VteTerminalCursorShape cursor_shape;

  GdkColor foreground;
  GdkColor background;
  GdkColor *colors;
  gint palette_size;
  gchar *font;

  STermKeySym *keys;
  gsize key_number;
} STermConfig;

STermConfig* sterm_configuration_new_default ();
STermConfig* sterm_configuration_parse_file ( gchar *config_file );
void sterm_configuration_destroy ( STermConfig *config );

#endif
