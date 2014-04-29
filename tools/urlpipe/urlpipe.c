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

#include <unistd.h>
#include <gio/gio.h>
#include <gio/gunixinputstream.h>

#include "defaults-global.h"

#ifndef DEFAULT_REGEX
#define DEFAULT_REGEX "\\b(([\\w-]+://?|www[.])[^\\s()<>]+(?:\\([\\w\\d]+\\)|([^[:punct:]\\s\\n]|/)))"
#endif

gchar *pattern = NULL;

void sterm_urlpipe_extract ( GDataInputStream *stream )
{
  GError *error = NULL;
  GMatchInfo *match = NULL;

  GRegex *regex = g_regex_new ( pattern, 0, 0, &error );

  if ( error ) {
    g_warning ( "ERROR: Failed to create URL regex: %s\n", error->message );
    g_clear_error ( &error );
    return;
  }

  GString *data = g_string_new ( "" );

  gchar *buffer;
  while ( buffer = g_data_input_stream_read_line ( stream, NULL, NULL, NULL ) )
    g_string_append_printf ( data, "%s\n", buffer );
  g_free ( buffer );

  g_regex_match ( regex, data->str, 0, &match );

  while ( g_match_info_matches ( match ) ) {
    gchar *word = g_match_info_fetch ( match, 0 );
    g_printf ( "%s\n", word );
    g_free ( word );
    g_match_info_next ( match, NULL );
  }

  g_match_info_free ( match );
  g_regex_unref ( regex );
  g_string_free ( data, TRUE );
}

int main ( int argc, char *argv[] )
{
  gchar *config_file = DEFAULT_CONFIG_FILE;
  GFile *file = NULL;
  GInputStream *stream = NULL;
  GKeyFile *keyfile = g_key_file_new ();

  if ( g_key_file_load_from_file ( keyfile, config_file, G_KEY_FILE_NONE, NULL ) ) {
    pattern = g_key_file_get_string ( keyfile, "urlpipe", "regex", NULL );
  }

  if ( pattern == NULL )
    pattern = g_strdup ( DEFAULT_REGEX );

  g_key_file_free ( keyfile );

  if ( argc > 1 ) {
    if ( g_strcmp0 ( argv[1], "-" ) == 0 ) {
      stream = g_unix_input_stream_new ( STDIN_FILENO, FALSE );
    } else {
      file = g_file_new_for_path ( argv[1] );
      if ( g_file_query_exists ( file, NULL ) )
        stream = (GInputStream*) g_file_read ( file, NULL, NULL );
    }
  } else {
    stream = g_unix_input_stream_new ( STDIN_FILENO, FALSE );
  }

  if ( stream ) {
    GDataInputStream *data_stream = g_data_input_stream_new ( stream );

    sterm_urlpipe_extract ( data_stream );

    g_input_stream_close ( stream, NULL, NULL );
  }

  g_free ( pattern );
  g_free ( config_file );
 
  return 0;
}
