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

#include "functions.h"

void sterm_functions_command_pipe ( STermTerminal *sterm, gchar *pipe )
{
  gchar *text = vte_terminal_get_text ( sterm->terminal, NULL, NULL, NULL );

  FILE *output = popen ( pipe, "w" );

  if ( output ) {
    fprintf ( output, "%s", text );

    if ( ! ferror ( output ) ) {

      if ( pclose ( output ) != 0 )
        g_warning ( "ERROR: Failed to close the pipe '%s'.\n", pipe );

    } else
      g_warning ( "ERROR: Failed to write to the pipe '%s'.\n", pipe );

  } else
    g_warning ( "ERROR: Failed to open the pipe '%s'.\n", pipe );

  g_free ( text );
}

void sterm_functions_paste ( STermTerminal *sterm, gchar *selection )
{
  if ( g_strcmp0 ( selection, "primary" ) == 0 )
    vte_terminal_paste_primary ( sterm->terminal );
  else if ( g_strcmp0 ( selection, "clipboard" ) == 0 )
    vte_terminal_paste_clipboard ( sterm->terminal );
}

void sterm_functions_zoom ( STermTerminal *sterm, gchar *factor )
{
  gint size = g_ascii_strtoll ( factor, NULL, 0 );

  PangoFontDescription *font = (PangoFontDescription*) vte_terminal_get_font ( sterm->terminal );
  pango_font_description_set_size ( font, pango_font_description_get_size ( font ) + size );
  vte_terminal_set_font ( sterm->terminal, font );
}

void sterm_functions_insert ( STermTerminal *sterm, gchar *text )
{
  vte_terminal_feed_child ( sterm->terminal, text, -1 );
}

void sterm_functions_set_font ( STermTerminal *sterm, gchar *font )
{
  PangoFontDescription *font_desc = pango_font_description_from_string ( font );
  vte_terminal_set_font ( sterm->terminal, font_desc );
}

void sterm_functions_init ( STermTerminal *sterm )
{
  sterm->functions = g_hash_table_new ( g_str_hash, g_str_equal );

  g_hash_table_insert ( sterm->functions, "command_pipe", sterm_functions_command_pipe );
  g_hash_table_insert ( sterm->functions, "insert", sterm_functions_insert );
  g_hash_table_insert ( sterm->functions, "paste", sterm_functions_paste );
  g_hash_table_insert ( sterm->functions, "set_font", sterm_functions_set_font );
  g_hash_table_insert ( sterm->functions, "zoom", sterm_functions_zoom );
}

