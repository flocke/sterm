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

#ifndef __STERM_FUNCTION_HANDLER_HPP
#define __STERM_FUNCTION_HANDLER_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "sterm/config.hpp"
#include "sterm/functions.hpp"
#include "sterm/terminal.hpp"

namespace sterm {

  typedef std::unordered_map<std::string, void(*)(sterm::terminal*, std::string)> function_map;

  class function_handler {
    private:
      /* Static map to the available functions */
      function_map          m_functions = {
        { "command_pipe", functions::command_pipe },
        { "insert", functions::insert },
        { "paste", functions::paste },
        { "reload_config", functions::reload_config },
        { "reset", functions::reset },
        { "set_font", functions::set_font },
        { "zoom", functions::zoom }
      };

      config               *m_configuration = NULL;
      terminal             *m_terminal = NULL;

      static gboolean       keypress_callback(GtkWidget *widget, GdkEventKey *event, function_handler *handler);

    public:
                            function_handler();
                            function_handler(config *configuration);
                            function_handler(terminal *terminal);
                            function_handler(config *configuration, terminal *terminal);

      void                  attach_config(config *configuration);
      void                  attach_to_terminal(terminal *terminal);

      void                  call_function(std::string function);

      gboolean              handle_keypress(GdkEventKey *event);
  };

}

#endif
