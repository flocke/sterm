/*
  Copyright (c) 2014-2015 Jakob Nixdorf <flocke@shadowice.org>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
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
  gboolean audible_bell;
  gboolean scroll_on_keystroke;
  gboolean scroll_on_output;
  gboolean rewrap_on_resize;
  gboolean mouse_autohide;
  // gchar *word_char_exceptions;
  gchar *encoding;

  VteCursorBlinkMode cursor_blink;
  VteCursorShape cursor_shape;

  GdkRGBA foreground;
  GdkRGBA background;
  GdkRGBA *colors;
  gint palette_size;
  PangoFontDescription *font;

  STermKeySym *keys;
  gsize key_number;
} STermConfig;

STermConfig* sterm_configuration_new_from_file ( gchar *config_file );
void sterm_configuration_destroy ( STermConfig *config );

#endif
