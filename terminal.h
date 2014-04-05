#ifndef _STERM_TERMINAL_H
#define _STERM_TERMINAL_H

#include <vte/vte.h>

#include "configuration.h"

#ifndef DEFAULT_CONFIG_FILE
#define DEFAULT_CONFIG_FILE g_build_path ( "/", g_get_home_dir(), "/.config/sterm/sterm.ini", NULL );
#endif

typedef struct {
  GtkWidget *main_window;
  GtkWidget *gtk_widget;
  VteTerminal *terminal;
  GPid child_pid;
} STermTerminal;

STermTerminal* sterm_terminal_new ();
void sterm_terminal_setup ( STermTerminal *sterm, STermConfig *config );
void sterm_terminal_start_child ( STermTerminal *sterm, gchar *command );

#endif
