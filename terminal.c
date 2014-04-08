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

#include "terminal.h"
#include "functions.h"

void sterm_terminal_destroy ( STermTerminal *sterm )
{
  g_hash_table_destroy ( sterm->functions );
  gtk_widget_destroy ( sterm->widget );
  g_free ( sterm );
}

void sterm_terminal_child_exited_cb ( VteTerminal *terminal, STermTerminal *sterm )
{
  sterm_terminal_destroy ( sterm );
}

void sterm_terminal_function_caller ( STermTerminal *sterm, gchar *string )
{
  gchar **command = g_strsplit ( string, " ", 2 );

  void (*func)(STermTerminal*, gchar*) = g_hash_table_lookup ( sterm->functions, command[0] );

  func ( sterm, command[1] );

  g_free ( command );
}

gboolean sterm_terminal_key_press_cb ( GtkWidget *main_win, GdkEventKey *event, STermTerminal *sterm )
{
  guint g = event->keyval;
  gint iter;

  for ( iter = 0; iter < sterm->config->key_number; iter++ ) {
    if ( ( event->state & ( sterm->config->keys[iter].modifier ) ) == ( sterm->config->keys[iter].modifier ) ) {
      if ( g == sterm->config->keys[iter].keyval ) {
        sterm_terminal_function_caller ( sterm, sterm->config->keys[iter].func );
        return TRUE;
      }
    }
  }

  return FALSE;
}

void sterm_terminal_setup ( STermTerminal *sterm )
{
  vte_terminal_set_scrollback_lines ( sterm->terminal, sterm->config->scrollback_lines );
  vte_terminal_set_allow_bold ( sterm->terminal, sterm->config->allow_bold );
  vte_terminal_set_audible_bell ( sterm->terminal, sterm->config->audible_bell );
  vte_terminal_set_visible_bell ( sterm->terminal, sterm->config->visible_bell );
  vte_terminal_set_scroll_on_keystroke ( sterm->terminal, sterm->config->scroll_on_keystroke );
  vte_terminal_set_scroll_on_output ( sterm->terminal, sterm->config->scroll_on_output );
  vte_terminal_set_rewrap_on_resize ( sterm->terminal, sterm->config->rewrap_on_resize );
  vte_terminal_set_mouse_autohide ( sterm->terminal, sterm->config->mouse_autohide );

  vte_terminal_set_cursor_blink_mode ( sterm->terminal, sterm->config->cursor_blink );
  vte_terminal_set_cursor_shape ( sterm->terminal, sterm->config->cursor_shape );

  vte_terminal_set_font_from_string ( sterm->terminal, sterm->config->font );
  vte_terminal_set_colors ( sterm->terminal, &sterm->config->foreground, &sterm->config->background, sterm->config->colors, sterm->config->palette_size );
}

void sterm_terminal_start_child ( STermTerminal *sterm, gchar *command )
{
  GError *error = NULL;
  gchar **args = 0;
  GSpawnFlags spawn_flags = G_SPAWN_SEARCH_PATH;

  gchar *user_shell = vte_get_user_shell ();

  if ( command == NULL )
    g_shell_parse_argv ( user_shell, 0, &args, 0 );
  else
    g_shell_parse_argv ( command, 0, &args, 0 );

  if ( ! vte_terminal_fork_command_full ( sterm->terminal, VTE_PTY_DEFAULT, NULL, args, NULL,
                                          spawn_flags, NULL, NULL, &sterm->child_pid, &error ) )
    g_warning ( "ERROR: Failed to spawn child: %s\n", error->message );
  else
    g_signal_connect ( G_OBJECT ( sterm->terminal ), "child-exited", G_CALLBACK ( sterm_terminal_child_exited_cb ), sterm );

  g_free ( args );
  g_free ( user_shell );
  if ( error )
    g_error_free ( error );
}

STermTerminal* sterm_terminal_new ( GtkWidget *container, STermConfig *config )
{
  STermTerminal *sterm = g_new0 ( STermTerminal, 1 );

  sterm->config = config;
  sterm->container = container;
  sterm_functions_init ( sterm );

  sterm->widget = vte_terminal_new ();
  sterm->terminal = VTE_TERMINAL ( sterm->widget );

  g_signal_connect ( G_OBJECT ( sterm->widget ), "key-press-event", G_CALLBACK ( sterm_terminal_key_press_cb ), sterm );

  return sterm;
}

