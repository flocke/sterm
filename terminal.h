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

#ifndef _STERM_TERMINAL_H
#define _STERM_TERMINAL_H

#include <vte/vte.h>

#include "configuration.h"

#ifndef DEFAULT_CONFIG_FILE
#define DEFAULT_CONFIG_FILE g_build_path ( "/", g_get_home_dir(), "/.config/sterm/sterm.ini", NULL );
#endif

typedef struct {
  STermConfig *config;
  GtkWidget *container;
  GtkWidget *widget;
  VteTerminal *terminal;
  GPid child_pid;
  GHashTable *functions;
} STermTerminal;

STermTerminal* sterm_terminal_new ( GtkWidget *container, STermConfig *config );
void sterm_terminal_setup ( STermTerminal *sterm );
void sterm_terminal_start_child ( STermTerminal *sterm, gchar *command );
void sterm_terminal_destroy ( STermTerminal *sterm );

#endif
