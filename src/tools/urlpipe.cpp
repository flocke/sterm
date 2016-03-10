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
#include <fstream>
#include <iostream>
#include <istream>
#include <istream>
#include <regex>
#include <string>

#include <glib.h>

#include "common/messages.hpp"
#include "common/xdg.hpp"

#ifndef DEFAULT_URL_REGEX
#define DEFAULT_URL_REGEX "\\b(([\\w-]+://?|www[.])[^\\s()<>]+(?:\\([\\w\\d]+\\)|([^[:punct:]\\s\\n]|/)))"
#endif

std::string read_file(std::string i_file_name) {
  std::ifstream stream(i_file_name, std::ios::in | std::ios::binary);

  if ( stream ) {
    std::string content;

    stream.seekg(0, std::ios::end);
    content.resize(stream.tellg());
    stream.seekg(0, std::ios::beg);

    stream.read(&content[0], content.size());

    stream.close();

    return(content);
  }

  return(std::string());
}

std::string read_stdin() {
  std::cin >> std::noskipws;

  std::istream_iterator<char> it(std::cin);
  std::istream_iterator<char> end;

  std::string content(it, end);

  return(content);
}

void parse_text(std::string i_text, std::string i_pattern) {
  try {
    std::regex regex(i_pattern);

    std::sregex_iterator next(i_text.begin(), i_text.end(), regex);
    std::sregex_iterator end;

    while ( next != end ) {
      std::smatch match = *next;
      std::cout << match.str() << std::endl;
      next++;
    }
  } catch(std::regex_error& error) {
    sterm::common::warning("sterm::tools::urlpipe", "failed to create regular expression: %s", i_pattern.c_str());
  }
}

int main(int argc, char *argv[]) {
  std::string config_file = sterm::common::xdg_config_file_path("sterm", "sterm.ini");

  std::string pattern;

  GKeyFile *keyfile = g_key_file_new();
  if ( g_key_file_load_from_file(keyfile, config_file.c_str(), G_KEY_FILE_NONE, NULL) ) {
    GError *error = NULL;

    gchar *temp = g_key_file_get_string(keyfile, "urlpipe", "regex", &error);

    if ( error == NULL ) {
      pattern = temp;
      g_free(temp);
    } else {
      g_error_free(error);
    }
  }

  g_key_file_free(keyfile);

  if ( pattern.empty() )
    pattern = DEFAULT_URL_REGEX;

  std::string text;

  if ( argc > 1 ) {
    if ( g_strcmp0(argv[1], "-") == 0 )
      text = read_stdin();
    else
      text = read_file(argv[1]);
  } else {
    text = read_stdin();
  }

  if ( ! text.empty() )
    parse_text(text, pattern);

  return(EXIT_SUCCESS);
}

