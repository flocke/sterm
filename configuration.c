#include "configuration.h"
#include "defaults.h"

STermConfig* new_default_config ()
{
  STermConfig *config = g_slice_new ( STermConfig );

  config->scrollback_lines = DEFAULT_SCROLLBACK_LINES;

  config->cursor_shape = DEFAULT_CURSOR_SHAPE;
  config->cursor_blink = DEFAULT_CURSOR_BLINK;

  config->font = DEFAULT_FONT;
  gdk_color_parse ( DEFAULT_COLOR_FOREGROUND, &config->foreground );
  gdk_color_parse ( DEFAULT_COLOR_BACKGROUND, &config->background );

  config->palette_size = DEFAULT_PALETTE_SIZE;
  config->colors = (GdkColor *) g_malloc ( sizeof ( GdkColor ) * DEFAULT_PALETTE_SIZE );
  gdk_color_parse ( DEFAULT_COLOR_COLOR0, &config->colors[0] );
  gdk_color_parse ( DEFAULT_COLOR_COLOR1, &config->colors[1] );
  gdk_color_parse ( DEFAULT_COLOR_COLOR2, &config->colors[2] );
  gdk_color_parse ( DEFAULT_COLOR_COLOR3, &config->colors[3] );
  gdk_color_parse ( DEFAULT_COLOR_COLOR4, &config->colors[4] );
  gdk_color_parse ( DEFAULT_COLOR_COLOR5, &config->colors[5] );
  gdk_color_parse ( DEFAULT_COLOR_COLOR6, &config->colors[6] );
  gdk_color_parse ( DEFAULT_COLOR_COLOR7, &config->colors[7] );
  gdk_color_parse ( DEFAULT_COLOR_COLOR8, &config->colors[8] );
  gdk_color_parse ( DEFAULT_COLOR_COLOR9, &config->colors[9] );
  gdk_color_parse ( DEFAULT_COLOR_COLOR10, &config->colors[10] );
  gdk_color_parse ( DEFAULT_COLOR_COLOR11, &config->colors[11] );
  gdk_color_parse ( DEFAULT_COLOR_COLOR12, &config->colors[12] );
  gdk_color_parse ( DEFAULT_COLOR_COLOR13, &config->colors[13] );
  gdk_color_parse ( DEFAULT_COLOR_COLOR14, &config->colors[14] );
  gdk_color_parse ( DEFAULT_COLOR_COLOR15, &config->colors[15] );

  return config;
}

STermConfig* parse_config_file ( gchar *config_file )
{
  GError *error = NULL;
  gchar *temp = NULL;
  int iter = 0;
  
  GKeyFile *keyfile = g_key_file_new ();
  STermConfig *config = new_default_config ();

  if ( ! g_key_file_load_from_file ( keyfile, config_file, G_KEY_FILE_NONE, &error ) ) {
    g_warning ( "ERROR: Failed to parse the config file %s: %s\n", config_file, error->message );
    return config;
  }

  /* General configuration */
  config->scrollback_lines = g_key_file_get_integer ( keyfile, "general", "scrollback", NULL );

  /* Cursor configuration */
  temp = g_key_file_get_string ( keyfile, "cursor", "shape", NULL );
  if ( g_strcmp0 ( temp, "block" ) == 0 )
    config->cursor_shape = VTE_CURSOR_SHAPE_BLOCK;
  else if ( g_strcmp0 ( temp, "beam" ) == 0 )
    config->cursor_shape = VTE_CURSOR_SHAPE_IBEAM;
  else if ( g_strcmp0 ( temp, "underline" ) == 0 )
    config->cursor_shape = VTE_CURSOR_SHAPE_UNDERLINE;

  temp = g_key_file_get_string ( keyfile, "cursor", "blink", NULL );
  if ( g_strcmp0 ( temp, "on" ) == 0 )
    config->cursor_blink = VTE_CURSOR_BLINK_ON;
  else if ( g_strcmp0 ( temp, "off" ) == 0 )
    config->cursor_blink = VTE_CURSOR_BLINK_OFF;
  else if ( g_strcmp0 ( temp, "system" ) == 0 )
    config->cursor_blink = VTE_CURSOR_BLINK_SYSTEM;

  /* Theme configuration */
  config->font = g_key_file_get_string ( keyfile, "theme", "font", NULL );

  gdk_color_parse ( g_key_file_get_string ( keyfile, "theme", "foreground", NULL ), &config->foreground );

  gdk_color_parse ( g_key_file_get_string ( keyfile, "theme", "background", NULL ), &config->background );

  for ( iter = 0; iter < DEFAULT_PALETTE_SIZE; iter++ ) {
    temp = g_strdup_printf ( "color%d", iter );
    gdk_color_parse ( g_key_file_get_string ( keyfile, "theme", temp, NULL ), &config->colors[iter] );
  }

  g_free ( temp );
  g_key_file_free ( keyfile );

  return config;
}

