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

#include "functions.h"

void command_pipe ( STermTerminal *sterm, gchar *pipe )
{
  gchar *text = vte_terminal_get_text ( sterm->terminal, NULL, NULL, NULL );

  FILE *output = popen ( pipe, "w" );
  if ( ! output ) {
    g_printf ( "ERROR: Could not open the pipe '%s'\n", pipe );
    return;
  }

  fprintf ( output, "%s", text );

  if ( ferror ( output ) ) {
    g_printf ( "ERROR: Output to pipe '%s' failed!\n", pipe );
    return;
  }

  if ( pclose ( output ) != 0 )
    g_printf ( "ERROR: Could not close the pipe '%s'\n", pipe );
}

void paste ( STermTerminal *sterm, gchar *selection )
{
  if ( g_strcmp0 ( selection, "primary" ) == 0 )
    vte_terminal_paste_primary ( sterm->terminal );
  else if ( g_strcmp0 ( selection, "clipboard" ) == 0 )
    vte_terminal_paste_clipboard ( sterm->terminal );
}

void initialize_functions ( STermTerminal *sterm )
{
  sterm->functions = g_hash_table_new ( g_str_hash, g_str_equal );

  g_hash_table_insert ( sterm->functions, "command_pipe", command_pipe );
  g_hash_table_insert ( sterm->functions, "paste", paste );
}

