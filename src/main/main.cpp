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

#include "common.hpp"
#include "config.hpp"
#include "function_handler.hpp"
#include "terminal.hpp"

std::string config_file = sterm::common::xdg_config_file_path("sterm", "sterm.ini");

int ret = EXIT_SUCCESS;
bool first = true;

GtkWidget *main_window = NULL;
sterm::config *configuration = NULL;
sterm::function_handler *functions = NULL;
sterm::terminal *terminal = NULL;

static gchar *opt_config_file = NULL;
static gchar *opt_command = NULL;

static GOptionEntry options[] {
  { "config", 'c', 0, G_OPTION_ARG_FILENAME, &opt_config_file, "Path to an alternative configuration file", NULL },
  { "execute", 'e', 0, G_OPTION_ARG_STRING, &opt_command, "Execute a command", NULL },
  { NULL }
};

static void main_exit_cb(GtkWidget *i_widget, GtkWidget** i_destroy) {
  if ( first ) {
    if ( i_destroy != NULL )
      gtk_widget_destroyed(i_widget, i_destroy);

    gtk_main_quit();
    first = false;
  }
}

static void main_exit_with_status_cb(GtkWidget *i_widget, int status) {
  if ( first ) {
    gtk_main_quit();
    ret = WIFEXITED(status) ? WEXITSTATUS(status) : EXIT_FAILURE;
    first = false;
  }
}

static void main_bell_cb(GtkWidget *i_widget) {
  if ( main_window != NULL ) {
    // Any old hint has to be removed for the window manager to
    // recognize the new one.
    gtk_window_set_urgency_hint(GTK_WINDOW(main_window), FALSE);

    if ( configuration != NULL )
      if ( configuration->get_urgent_on_bell() )
        gtk_window_set_urgency_hint(GTK_WINDOW(main_window), TRUE);
  }
}

static gboolean parse_commandline(int argc, char* argv[]) {
  gboolean success = true;
  GError *error = NULL;

  GOptionContext *context = g_option_context_new(NULL);

  g_option_context_set_summary(context, "STerm - a simple terminal emulator based on the VTE library");
  g_option_context_add_main_entries(context, options, NULL);
  g_option_context_add_group(context, gtk_get_option_group(true));

  if ( ! g_option_context_parse(context, &argc, &argv, &error) ) {
    g_warning("failed to parse the commandline options: %s", error->message);
    g_error_free(error);
    success = false;
  }

  g_option_context_free(context);

  return(success);
}

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  if ( ! parse_commandline(argc, argv) )
    return(EXIT_FAILURE);

  if ( opt_config_file != NULL )
    config_file = opt_config_file;

  configuration = new sterm::config(config_file);

  gtk_window_set_default_icon_name("utilities-terminal");

  main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(main_window), "STerm");
  gtk_container_set_border_width(GTK_CONTAINER(main_window), 0);

  terminal = new sterm::terminal(configuration);

  std::string child_command;
  if ( opt_command != NULL )
    child_command = opt_command;

  terminal->attach_to_container(GTK_CONTAINER(main_window));

  terminal->spawn_child(child_command);

  terminal->connect_callback("child-exited", G_CALLBACK(main_exit_with_status_cb), NULL);
  terminal->connect_callback("bell", G_CALLBACK(main_bell_cb), NULL);

  terminal->link_property_to_terminal("window-title", G_OBJECT(main_window), "title");

  g_signal_connect(G_OBJECT(main_window), "destroy", G_CALLBACK(main_exit_cb), &main_window);

  functions = new sterm::function_handler(configuration, terminal);

  gtk_widget_show_all(main_window);
  gtk_main();

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

  if ( main_window != NULL ) {
    gtk_widget_destroy(main_window);
    main_window = NULL;
  }

  return ret;
}

