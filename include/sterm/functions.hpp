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

#ifndef __STERM_FUNCTIONS_HPP
#define __STERM_FUNCTIONS_HPP

#include <string>

#include "sterm/terminal.hpp"

namespace sterm {
  namespace functions {

    void      command_pipe(sterm::terminal *terminal, std::string command);
    void      insert(sterm::terminal *terminal, std::string text);
    void      paste(sterm::terminal *terminal, std::string selection);
    void      reload_config(sterm::terminal *terminal, std::string none);
    void      set_font(sterm::terminal *terminal, std::string font);
    void      zoom(sterm::terminal *terminal, std::string factor);

  }
}

#endif
