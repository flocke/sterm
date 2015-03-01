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
