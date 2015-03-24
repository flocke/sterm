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

  if ( func )
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
  GError *error = NULL;

  vte_terminal_set_scrollback_lines ( sterm->terminal, sterm->config->scrollback_lines );
  vte_terminal_set_allow_bold ( sterm->terminal, sterm->config->allow_bold );
  vte_terminal_set_audible_bell ( sterm->terminal, sterm->config->audible_bell );
  vte_terminal_set_scroll_on_keystroke ( sterm->terminal, sterm->config->scroll_on_keystroke );
  vte_terminal_set_scroll_on_output ( sterm->terminal, sterm->config->scroll_on_output );
  vte_terminal_set_rewrap_on_resize ( sterm->terminal, sterm->config->rewrap_on_resize );
  vte_terminal_set_mouse_autohide ( sterm->terminal, sterm->config->mouse_autohide );
  // vte_terminal_set_word_char_exceptions ( sterm->terminal, sterm->config->word_char_exceptions );
  if ( ! vte_terminal_set_encoding ( sterm->terminal, sterm->config->encoding, &error ) )
    g_warning ( "WARNING: Failed to set terminal encoding: %s\n", error->message );

  vte_terminal_set_cursor_blink_mode ( sterm->terminal, sterm->config->cursor_blink );
  vte_terminal_set_cursor_shape ( sterm->terminal, sterm->config->cursor_shape );

  vte_terminal_set_font ( sterm->terminal, sterm->config->font );
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

  if ( ! vte_terminal_spawn_sync ( sterm->terminal, VTE_PTY_DEFAULT, NULL, args, NULL,
                                          spawn_flags, NULL, NULL, &sterm->child_pid, NULL, &error ) )
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

