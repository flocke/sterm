#include "terminal.h"

static void sterm_terminal_exit ()
{
  gtk_main_quit ();
}

static void sterm_terminal_title_changed_cb ( GtkWidget *terminal, STermTerminal *sterm )
{
  const gchar *title = vte_terminal_get_window_title ( VTE_TERMINAL ( terminal ) );

  if ( title == NULL )
    title = "sterm";

  gtk_window_set_title ( GTK_WINDOW ( sterm->main_window ), title );
}

void sterm_terminal_setup ( STermTerminal *sterm, STermConfig *config )
{
  vte_terminal_set_font_from_string ( sterm->terminal, config->font );
  vte_terminal_set_colors ( sterm->terminal, &config->foreground, &config->background, config->colors, config->palette_size );
  vte_terminal_set_cursor_blink_mode ( sterm->terminal, config->cursor_blink );
  vte_terminal_set_cursor_shape ( sterm->terminal, config->cursor_shape );
  vte_terminal_set_scrollback_lines ( sterm->terminal, config->scrollback_lines );

  g_signal_connect ( G_OBJECT ( sterm->terminal ), "window-title-changed", G_CALLBACK ( sterm_terminal_title_changed_cb ), sterm );
}

void sterm_terminal_start_child ( STermTerminal *sterm, gchar *command )
{
  if ( command == NULL )
    command = vte_get_user_shell ();

  gchar *child_command[2] = { command, 0 };

  vte_terminal_fork_command_full ( sterm->terminal, VTE_PTY_DEFAULT, NULL, child_command, NULL,
                                   G_SPAWN_SEARCH_PATH, NULL, NULL, &sterm->child_pid, NULL );

  g_signal_connect ( G_OBJECT ( sterm->terminal ), "child-exited", G_CALLBACK ( sterm_terminal_exit ), NULL );
}

STermTerminal* sterm_terminal_new ()
{
  STermTerminal *sterm = g_new0 ( STermTerminal, 1 );

  sterm->main_window = gtk_window_new ( GTK_WINDOW_TOPLEVEL );
  gtk_window_set_title ( GTK_WINDOW ( sterm->main_window ), "sterm" );
  gtk_container_set_border_width ( GTK_CONTAINER ( sterm->main_window ), 0 );
  g_signal_connect ( G_OBJECT ( sterm->main_window ), "destroy", G_CALLBACK ( sterm_terminal_exit ), NULL );

  sterm->gtk_widget = vte_terminal_new ();
  sterm->terminal = VTE_TERMINAL ( sterm->gtk_widget );

  gtk_container_add ( GTK_CONTAINER ( sterm->main_window ), sterm->gtk_widget );

  return sterm;
}

