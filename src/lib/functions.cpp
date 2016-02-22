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

    void set_font(sterm::terminal *i_terminal, std::string i_font) {
      if ( i_terminal != NULL ) {
        PangoFontDescription *font = pango_font_description_from_string(i_font.c_str());
        if ( font != NULL ) {
          i_terminal->set_font_description(&font);
          pango_font_description_free(font);
        }
      }
    }

    void zoom(sterm::terminal *i_terminal, std::string i_increase) {
      if ( i_terminal != NULL ) {
        int increase = 1;
        
        try {
          increase = std::stoi(i_increase);
        } catch (const std::exception& except) {
          g_warning("unable to convert string to int: %s", i_increase);
          return;
        }

        PangoFontDescription *desc = NULL;
        if ( i_terminal->copy_font_description(&desc) ) {
          gint size = pango_font_description_get_size(desc);
          size += increase * PANGO_SCALE;

          pango_font_description_set_size(desc, size);

          i_terminal->set_font_description(&desc);
          pango_font_description_free(desc);
        }
      }
    }

  }

}

