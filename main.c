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

#include <gtk/gtk.h>

#include "terminal.h"
#include "configuration.h"

static gchar *config_file = NULL;
static gchar *run_app = NULL;

static STermTerminal *sterm;
static STermConfig *config;

static GOptionEntry options[] = {
  { "config", 'c', 0, G_OPTION_ARG_FILENAME, &config_file, "Path to the configuration file to use.", NULL },
  { "execute", 'e', 0, G_OPTION_ARG_STRING, &run_app, "Execute the given command.", NULL },
  { NULL }
};

static gboolean parse_commandline ( int argc, char* argv[] )
{
  gboolean retval = TRUE;
  GError *error = NULL;
  
  GOptionContext *context = g_option_context_new ( "- a simple VTE based terminal emulator" );
  g_option_context_add_main_entries ( context, options, NULL );
  g_option_context_add_group ( context, gtk_get_option_group ( TRUE ) );
  if ( ! g_option_context_parse ( context, &argc, &argv, &error ) ) {
    g_error ( "ERROR: Failed to parse command-line options: %s\n", error->message );
    retval = FALSE;
  }
  
  return retval;
}

int main ( int argc, char* argv[] )
{
  gtk_init ( &argc, &argv );

  if ( ! parse_commandline ( argc, argv ) )
    return 1;

  if ( config_file == NULL )
    config_file = DEFAULT_CONFIG_FILE;

  config = parse_config_file ( config_file );

  sterm = sterm_terminal_new ( config );
  sterm_terminal_setup ( sterm );
  sterm_terminal_start_child ( sterm, run_app );

  gtk_widget_show_all ( sterm->main_window );
  gtk_main ();

  return 0;
}

