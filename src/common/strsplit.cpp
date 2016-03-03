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

#include <sstream>

#include "common.hpp"

namespace sterm {
  namespace common {

    std::vector<std::string> split(std::string i_input, const char i_delim) {
      std::vector<std::string> output;

      std::stringstream stream(i_input);

      std::string item;
      while ( std::getline(stream, item, i_delim) )
        output.push_back(item);

      return(output);
    }

    std::vector<std::string> split(std::string i_input, const char i_delim, int i_length) {
      std::vector<std::string> output;

      std::stringstream stream(i_input);

      std::string item;
      for ( int i = 0; i < i_length - 1; i++ )
        if ( ! stream.eof() ) {
          std::getline(stream, item, i_delim);
          output.push_back(item);
        }

      if ( ! stream.eof() )
        output.push_back(std::string(std::istreambuf_iterator<char>(stream), {}));

      return(output);
    }

  }
}

