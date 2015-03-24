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

#include "configuration.h"
#include "defaults-config.h"

void sterm_configuration_destroy ( STermConfig *config )
{
  g_free ( config->word_chars );
  g_free ( config->font );
  g_free ( config->colors );
  g_free ( config->keys );
  g_free ( config );
}

gchar* sterm_configuration_get_string ( GKeyFile *keyfile, const gchar *section, const gchar* key, gchar* default_value )
{
  if ( keyfile ) {
    GError *error = NULL;

    gchar *value = g_key_file_get_string ( keyfile, section, key, &error );

    if ( error ) {
      value = g_strdup ( default_value );
      g_error_free ( error );
    }

    return value;
  } else
    return g_strdup ( default_value );
}

gboolean sterm_configuration_get_boolean ( GKeyFile *keyfile, const gchar *section, const gchar* key, gboolean default_value )
{
  if ( keyfile ) {
    GError *error = NULL;

    gboolean value = g_key_file_get_boolean ( keyfile, section, key, &error );

    if ( error ) {
      value = default_value;
      g_error_free ( error );
    }

    return value;
  } else {
    return default_value;
  }
}

gint sterm_configuration_get_integer ( GKeyFile *keyfile, const gchar *section, const gchar *key, gint default_value )
{
  if ( keyfile ) {
    GError *error = NULL;

    gint value = g_key_file_get_integer ( keyfile, section, key, &error );

    if ( error ) {
      value = default_value;
      g_error_free ( error );
    }

    return value;
  } else
    return default_value;
}

void sterm_configuration_load_keys ( STermConfig *config, GKeyFile *keyfile ) {
  int iter = 0;

  gchar **keys = g_key_file_get_keys ( keyfile, "keys", &config->key_number, NULL );

  config->keys = g_new0 ( STermKeySym, config->key_number );

  for ( iter = 0; iter < config->key_number; iter++ ) {
    gchar **parts = g_strsplit ( keys[iter], "-", 0 );
    guint length = g_strv_length ( parts );

    int i = 0;
    for ( i = 0; i < length - 1; i++ ) {
      if ( g_strcmp0 ( parts[i], "Mod1" ) == 0 )
        config->keys[iter].modifier |= GDK_MOD1_MASK;
      else if ( g_strcmp0 ( parts[i], "Control" ) == 0 )
        config->keys[iter].modifier |= GDK_CONTROL_MASK;
      else if ( g_strcmp0 ( parts[i], "Shift" ) == 0 ) {
        config->keys[iter].modifier |= GDK_SHIFT_MASK;
      }
    }

    config->keys[iter].keyval = gdk_keyval_from_name ( parts[length - 1] );

    config->keys[iter].func = g_key_file_get_string ( keyfile, "keys", keys[iter], NULL );

    g_free ( parts );
  }

  g_free ( keys );
}

STermConfig* sterm_configuration_new_from_file ( gchar *config_file )
{
  GError *error = NULL;
  gchar *temp = NULL;
  int iter = 0;
  
  GKeyFile *keyfile = g_key_file_new ();
  g_key_file_load_from_file ( keyfile, config_file, G_KEY_FILE_NONE, &error );

  if ( error ) {
    g_warning ( "ERROR: Failed to parse the config file %s: %s\n", config_file, error->message );
    keyfile = NULL;
    g_error_free ( error );
  }

  STermConfig *config = g_new0 ( STermConfig, 1 );

  /* General configuration */
  config->scrollback_lines = sterm_configuration_get_integer ( keyfile, "general", "scrollback", DEFAULT_SCROLLBACK_LINES );
  config->allow_bold = sterm_configuration_get_boolean ( keyfile, "general", "allow_bold", DEFAULT_ALLOW_BOLD );
  config->audible_bell = sterm_configuration_get_boolean ( keyfile, "general", "audible_bell", DEFAULT_AUDIBLE_BELL );
  config->scroll_on_keystroke = sterm_configuration_get_boolean ( keyfile, "general", "scroll_on_keystroke", DEFAULT_SCROLL_ON_KEYSTROKE );
  config->scroll_on_output = sterm_configuration_get_boolean ( keyfile, "general", "scroll_on_output", DEFAULT_SCROLL_ON_OUTPUT );
  config->rewrap_on_resize = sterm_configuration_get_boolean ( keyfile, "general", "rewrap_on_resize", DEFAULT_REWRAP_ON_RESIZE );
  config->word_chars = sterm_configuration_get_string ( keyfile, "general", "word_chars", DEFAULT_WORD_CHARS );
  config->encoding = sterm_configuration_get_string ( keyfile, "general", "encoding", DEFAULT_ENCODING );

  /* Cursor configuration */
  temp = sterm_configuration_get_string ( keyfile, "cursor", "shape", DEFAULT_CURSOR_SHAPE );
  if ( g_strcmp0 ( temp, "block" ) == 0 )
    config->cursor_shape = VTE_CURSOR_SHAPE_BLOCK;
  else if ( g_strcmp0 ( temp, "beam" ) == 0 )
    config->cursor_shape = VTE_CURSOR_SHAPE_IBEAM;
  else if ( g_strcmp0 ( temp, "underline" ) == 0 )
    config->cursor_shape = VTE_CURSOR_SHAPE_UNDERLINE;

  temp = sterm_configuration_get_string ( keyfile, "cursor", "blink", DEFAULT_CURSOR_BLINK );
  if ( g_strcmp0 ( temp, "on" ) == 0 )
    config->cursor_blink = VTE_CURSOR_BLINK_ON;
  else if ( g_strcmp0 ( temp, "off" ) == 0 )
    config->cursor_blink = VTE_CURSOR_BLINK_OFF;
  else if ( g_strcmp0 ( temp, "system" ) == 0 )
    config->cursor_blink = VTE_CURSOR_BLINK_SYSTEM;

  /* Theme configuration */
  config->font = sterm_configuration_get_string ( keyfile, "theme", "font", DEFAULT_FONT );

  temp = sterm_configuration_get_string ( keyfile, "theme", "foreground", DEFAULT_COLOR_FOREGROUND );
  gdk_color_parse ( temp, &config->foreground );

  temp = sterm_configuration_get_string ( keyfile, "theme", "background", DEFAULT_COLOR_BACKGROUND );
  gdk_color_parse ( temp, &config->background );

  config->palette_size = DEFAULT_PALETTE_SIZE;

  gchar **default_colors = g_strsplit ( DEFAULT_COLOR_PALETTE, " ", DEFAULT_PALETTE_SIZE );
  config->colors = g_new0 ( GdkColor, DEFAULT_PALETTE_SIZE );
  for ( iter = 0; iter < DEFAULT_PALETTE_SIZE; iter++ ) {
    temp = sterm_configuration_get_string ( keyfile, "theme", g_strdup_printf ( "color%d", iter ), default_colors[iter] );
    gdk_color_parse ( temp, &config->colors[iter] );
  }
  g_free ( default_colors );

  if ( keyfile ) {
    /* Keys */
    sterm_configuration_load_keys ( config, keyfile );

    g_key_file_free ( keyfile );
  }

  g_free ( temp );

  return config;
}

