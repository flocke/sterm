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

#include "sterm/functions.hpp"
#include "sterm/terminal.hpp"

namespace sterm {
  namespace functions {

    void command_pipe(sterm::terminal *i_terminal, std::string i_command) {
      if ( i_terminal != NULL ) {
        std::string text = i_terminal->get_text();

        FILE *output = popen(i_command.c_str(), "w");

        if ( output ) {
          fprintf(output, "%s", text.c_str());

          if ( ! ferror(output) ) {
            if ( pclose(output) != 0 )
              g_warning("failed to close the pipe: %s", i_command);
          } else {
            g_warning("failed to write to the pipe: %s", i_command);
          }
        } else {
          g_warning("failed to open the pipe: %s", i_command);
        }
      }
    }

    void insert(sterm::terminal *i_terminal, std::string i_text) {
      if ( i_terminal != NULL ) {
        i_terminal->insert_text(i_text);
      }
    }

    void paste(sterm::terminal *i_terminal, std::string i_buffer) {
      if ( i_terminal != NULL ) {
        if ( i_buffer.compare("primary") == 0 )
          i_terminal->paste(PRIMARY);
        else if ( i_buffer.compare("clipboard") == 0 )
          i_terminal->paste(CLIPBOARD);
      }
    }

    void reload_config(sterm::terminal *i_terminal, std::string nothing) {
      if ( i_terminal != NULL )
        i_terminal->reload_configuration();
    }

    void reset(sterm::terminal *i_terminal, std::string full) {
      if ( i_terminal != NULL ) {
        if ( full.compare("full") == 0 )
          i_terminal->reset_terminal(true);
        else
          i_terminal->reset_terminal(false);
      }
    }

    void set_font(sterm::terminal *i_terminal, std::string i_font) {
      if ( i_terminal != NULL ) {
        PangoFontDescription *font = pango_font_description_from_string(i_font.c_str());
        if ( font != NULL ) {
          i_terminal->set_font_description(&font);
          pango_font_description_free(font);
        }
      }
    }

    void set_font_scale(sterm::terminal *i_terminal, std::string i_scale) {
      if ( i_terminal != NULL ) {
        double sc = 1;

        try {
          sc = std::stod(i_scale);
        } catch(const std::exception& except) {
          g_warning("unable to convert string to double: %s", i_scale.c_str());
          return;
        }

        i_terminal->set_font_scale(sc);
      }
    }

    void zoom(sterm::terminal *i_terminal, std::string i_factor) {
      if ( i_terminal != NULL ) {
        double inc = 0;

        try {
          inc = std::stod(i_factor);
        } catch(const std::exception& except) {
          g_warning("unable to convert string to double: %s", i_factor.c_str());
          return;
        }

        double cur = i_terminal->get_font_scale();
        cur = cur + inc;

        i_terminal->set_font_scale(cur);
      }
    }

  }
}

