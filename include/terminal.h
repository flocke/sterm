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

#ifndef _STERM_TERMINAL_H
#define _STERM_TERMINAL_H

#include <vte/vte.h>

#include "configuration.h"

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
