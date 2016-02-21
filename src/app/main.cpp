/*
  Copyright (c) 2016 Jakob Nixdorf <flocke@shadowice.org>

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

#include <cstdlib>
#include <gtk/gtk.h>

#include "sterm/config.hpp"
#include "sterm/function_handler.hpp"
#include "sterm/terminal.hpp"

std::string config_file = g_build_path ( "/", g_get_home_dir(), "/.config/sterm/sterm.ini", NULL );

GtkWidget *main_window = NULL;
sterm::config *configuration = NULL;
sterm::function_handler *functions = NULL;
sterm::terminal *terminal = NULL;

gboolean running = false;

static gchar *opt_config_file = NULL;
static gchar *opt_command = NULL;

static GOptionEntry options[] {
  { "config", 'c', 0, G_OPTION_ARG_FILENAME, &opt_config_file, "Path to an alternative configuration file", NULL },
  { "execute", 'e', 0, G_OPTION_ARG_STRING, &opt_command, "Execute a command", NULL },
  { NULL }
};

static void main_exit() {
  gtk_main_quit();

  if ( terminal != NULL ) {
    delete(terminal);
    terminal = NULL;
  }

  if ( functions != NULL ) {
    delete(functions);
    functions = NULL;
  }

  if ( configuration != NULL ) {
    delete(configuration);
    configuration = NULL;
  }

  running = false;

  exit(EXIT_SUCCESS);
}

static gboolean parse_commandline(int argc, char* argv[]) {
  gboolean success = true;
  GError *error = NULL;

  GOptionContext *context = g_option_context_new(" - a simple terminal emulator based on VTE");
  g_option_context_add_main_entries(context, options, NULL);
  g_option_context_add_group(context, gtk_get_option_group(true));
  if ( ! g_option_context_parse(context, &argc, &argv, &error) ) {
    g_warning("failed to parse the commandline options: %s", error->message);
    g_error_free(error);
    success = false;
  }

  return(success);
}

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  if ( ! parse_commandline(argc, argv) )
    return(EXIT_FAILURE);

  if ( opt_config_file != NULL )
    config_file = opt_config_file;

  configuration = new sterm::config(config_file);

  main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(main_window), "sterm");
  gtk_container_set_border_width(GTK_CONTAINER(main_window), 0);

  terminal = new sterm::terminal(configuration);

  std::string child_command;
  if ( opt_command != NULL )
    child_command = opt_command;

  terminal->spawn_child(child_command);

  terminal->attach_to_container(GTK_CONTAINER(main_window));

  terminal->connect_callback("destroy", G_CALLBACK(main_exit));
  terminal->connect_callback("child-exited", G_CALLBACK(main_exit));

  terminal->link_property_to_terminal("window-title", G_OBJECT(main_window), "title");

  g_signal_connect(G_OBJECT(main_window), "destroy", G_CALLBACK(main_exit), NULL);

  functions = new sterm::function_handler(configuration, terminal);

  gtk_widget_show_all(main_window);
  running = true;
  gtk_main();

  return(EXIT_FAILURE);
}

