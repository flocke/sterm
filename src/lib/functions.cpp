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

namespace sterm {
  namespace functions {

    void command_pipe(sterm::terminal *i_terminal, std::string command) {
      if ( i_terminal != NULL ) {
        std::string text = i_terminal->get_text();

        FILE *output = popen(command.c_str(), "w");

        if ( output ) {
          fprintf(output, "%s", text.c_str());

          if ( ! ferror(output) ) {
            if ( pclose(output) != 0 )
              g_warning("failed to close the pipe: %s", command);
          } else {
            g_warning("failed to write to the pipe: %s", command);
          }
        } else {
          g_warning("failed to open the pipe: %s", command);
        }
      }
    }

  }
}

