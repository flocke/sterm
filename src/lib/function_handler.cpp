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

#include <iostream>

#include "sterm/function_handler.hpp"

namespace sterm {

  function_handler::function_handler() {}

  function_handler::function_handler(config *i_configuration) {
    this->load_keys_from_config(i_configuration);
  }

  function_handler::function_handler(terminal *i_terminal) {
    this->attach_to_terminal(i_terminal);
  }

  function_handler::function_handler(config *i_configuration, terminal *i_terminal) {
    this->load_keys_from_config(i_configuration);
    this->attach_to_terminal(i_terminal);
  }

  gboolean function_handler::keypress_callback(GtkWidget *i_widget, GdkEventKey *i_event, function_handler *i_handler) {
    if ( i_handler != NULL )
      return(i_handler->handle_keypress(i_event));

    return(false);
  }

  void function_handler::load_keys_from_config(config *i_configuration) {
    if ( i_configuration != NULL )
      m_keys = i_configuration->get_keys();
  }

  void function_handler::attach_to_terminal(terminal *i_terminal) {
    if ( i_terminal != NULL ) {
      m_terminal = i_terminal;

      m_terminal->connect_callback("key-press-event", G_CALLBACK(keypress_callback), (void*)this);
    }
  }

  void function_handler::call_function(std::string i_command) {
    if ( ! i_command.empty() ) {
      gchar **command = g_strsplit(i_command.c_str(), " ", 2);

      void (*func)(terminal*, std::string) = NULL;

      try {
        func = m_functions.at(command[0]);
      } catch (const std::out_of_range& except) {
        g_warning("unknown function called: %s", command[0]);
      }

      if ( func != NULL )
        func(m_terminal, command[1]);

      g_free(command);
    }
  }

  gboolean function_handler::handle_keypress(GdkEventKey *i_event) {
    guint keyval = i_event->keyval;
    guint modifier = i_event->state;

    for ( int iter = 0; iter < m_keys.size(); iter++ ) {
      if ( ( modifier & ( m_keys[iter].modifier ) ) == ( m_keys[iter].modifier ) ) {
        if ( keyval == m_keys[iter].keyval ) {
          this->call_function(m_keys[iter].function);
          return(true);
        }
      }
    }

    return(false);
  }

}

