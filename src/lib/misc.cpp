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
#include <iostream>

#include <glib.h>

#include "sterm/misc.hpp"

namespace sterm {
  namespace misc {

    std::string xdg_config_file_path(std::string i_app_name, std::string i_file_name) {
      const char *xdg = std::getenv("XDG_CONFIG_HOME");

      if ( xdg != NULL && xdg[0] != '\0' ) {
        return(g_build_path("/", xdg, i_app_name.c_str(), i_file_name.c_str(), NULL));
      } else
        return(g_build_path("/", g_get_home_dir(), ".config", i_app_name.c_str(), i_file_name.c_str(), NULL));
    }

  }
}

