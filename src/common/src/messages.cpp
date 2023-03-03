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

#include <cstdarg>
#include <cstdio>
#include <iostream>

#include "common/messages.hpp"

namespace sterm {
  namespace common {
    bool debugging = false;

    void set_debugging(bool i_val) {
      debugging = i_val;
    }

    void warning(std::string i_source, std::string i_format, ...) {
      va_list variable_args;

      va_start(variable_args, i_format);

      std::cerr << "[" << i_source << "] [warning] ";
      vfprintf(stderr, i_format.c_str(), variable_args);
      std::cerr << std::endl;

      va_end(variable_args);
    }

    void error(std::string i_source, std::string i_format, ...) {
      va_list variable_args;

      va_start(variable_args, i_format);

      std::cerr << "[" << i_source << "] [error] ";
      vfprintf(stderr, i_format.c_str(), variable_args);
      std::cerr << std::endl;

      va_end(variable_args);
    }

    void debug(std::string i_source, std::string i_format, ...) {
      if ( debugging ) {
        va_list variable_args;

        va_start(variable_args, i_format);

        std::cerr << "[" << i_source << "] [debug] ";
        vfprintf(stderr, i_format.c_str(), variable_args);
        std::cerr << std::endl;

        va_end(variable_args);
      }
    }

  }
}

