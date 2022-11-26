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
#include <iterator>
#include <regex>
#include <string>

#include <glib.h>

#include "common/messages.hpp"
#include "common/xdg.hpp"

#ifndef FALLBACK_REGEX
#define FALLBACK_REGEX "\\b(([\\w-]+://?|www[.])[^\\s()<>]+(?:\\([\\w\\d]+\\)|([^[:punct:]\\s\\n]|/)))"
#endif

/** Options **/
static gboolean opt_debug = false;
static gchar *opt_config_file = NULL;
static gchar *opt_file = NULL;
static gchar *opt_regex = NULL;

static GOptionEntry options[] {
  { "config", 'c', 0, G_OPTION_ARG_FILENAME, &opt_config_file, "Path to an alternative configuration file", NULL },
  { "debug", 'd', 0, G_OPTION_ARG_NONE, &opt_debug, "Enable additional debug output", NULL },
  { "file", 'f', 0, G_OPTION_ARG_FILENAME, &opt_file, "File to read the text from", NULL },
  { "regex", 'r', 0, G_OPTION_ARG_STRING, &opt_regex, "Regular expression to use", NULL },
  { NULL }
};

GError *error = NULL;
GKeyFile *keyfile = NULL;

/** Functions **/

void main_cleanup() {
  if ( error != NULL ) {
    g_error_free(error);
    error = NULL;
  }

  if ( keyfile != NULL ) {
    g_key_file_free(keyfile);
    keyfile = NULL;
  }

  if ( opt_config_file != NULL ) {
    g_free(opt_config_file);
    opt_config_file = NULL;
  }

  if ( opt_file != NULL ) {
    g_free(opt_file);
    opt_file = NULL;
  }

  if ( opt_regex != NULL ) {
    g_free(opt_regex);
    opt_regex = NULL;
  }
}

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
    sterm::common::warning("sterm::tools::matchmaker", "failed to create regular expression: %s", i_pattern.c_str());
  }
}

std::string get_default_regex(GKeyFile *i_keyfile) {
  GError *read_error = NULL;

  std::string regex;

  gchar *pattern = g_key_file_get_value(i_keyfile, "general", "default", &read_error);

  if ( read_error == NULL ) {
    regex = pattern;
    g_free(pattern);
  } else {
    g_error_free(read_error);
    read_error = NULL;
  }

  return(regex);
}

std::string get_regex(GKeyFile *i_keyfile, std::string i_regex) {
  GError *read_error = NULL;

  std::string regex;

  gchar *pattern = g_key_file_get_value(i_keyfile, "regex", i_regex.c_str(), &read_error);

  if ( read_error == NULL ) {
    regex = pattern;
    g_free(pattern);
  } else {
    g_error_free(read_error);
    read_error = NULL;
  }

  return(regex);
}

static gboolean parse_commandline(int argc, char *argv[]) {
  gboolean success = true;
  GError *cmd_error = NULL;

  GOptionContext *context = g_option_context_new(NULL);

  g_option_context_add_main_entries(context, options, NULL);

  if ( ! g_option_context_parse(context, &argc, &argv, &cmd_error) ) {
    success = false;

    g_error_free(cmd_error);
    cmd_error = NULL;
  }

  g_option_context_free(context);

  return(success);
}

/** Main **/

int main(int argc, char *argv[]) {
  std::string config_file = sterm::common::xdg_config_file_path("sterm", "matchmaker.ini");

  if ( ! parse_commandline(argc, argv) )
    return(EXIT_FAILURE);

  sterm::common::set_debugging(opt_debug);

  std::string regex_name;
  std::string regex_pattern;

  if ( opt_config_file != NULL )
    config_file = opt_config_file;
  if ( opt_regex != NULL )
    regex_name = opt_regex;

  keyfile = g_key_file_new();
  g_key_file_load_from_file(keyfile, config_file.c_str(), G_KEY_FILE_NONE, &error);

  if ( error == NULL ) {
    bool using_default = false;

    if ( regex_name.empty() ) {
      regex_name = get_default_regex(keyfile);

      if ( regex_name.empty() ) {
        sterm::common::debug("sterm::tools::matchmaker", "no regex specified and no default regex set, falling back to the built-in URL-matching regex");

        regex_pattern = FALLBACK_REGEX;
      } else {
        using_default = true;
      }
    } 
    
    if ( regex_pattern.empty() ) { // Not using the fallback pattern
      regex_pattern = get_regex(keyfile, regex_name);

      if ( regex_pattern.empty() ) {
        if ( using_default ) {
          sterm::common::error("sterm::tools::matchmaker", "default regex '%s' not found", regex_name.c_str());

          main_cleanup();
          return(EXIT_FAILURE);
        } else {
          sterm::common::error("sterm::tools::matchmaker", "requested regex '%s' not found", regex_name.c_str());

          main_cleanup();
          return(EXIT_FAILURE);
        }
      }

      if ( using_default )
        sterm::common::debug("sterm::tools::matchmaker", "using default regex '%s'", regex_name.c_str());
    }

    g_key_file_free(keyfile);
    keyfile = NULL;
  } else {
    if ( error->code != G_KEY_FILE_ERROR_NOT_FOUND && error->code != G_FILE_ERROR_NOENT ) {
      sterm::common::error("sterm::common::matchmaker", "unable to load config file '%s'", config_file.c_str());
      sterm::common::debug("sterm::common::matchmaker", "GKeyFile error message: %s", error->message);

      main_cleanup();
      return(EXIT_FAILURE);
    } else {
      if ( opt_regex != NULL ) {
        sterm::common::error("sterm::common::matchmaker", "regex '%s' was requested, but no config file could be found", regex_name.c_str());

        main_cleanup();
        return(EXIT_FAILURE);
      } else {
        sterm::common::debug("sterm::common::matchmaker", "no config file found, falling back to built-in URL-matching regex");

        regex_pattern = FALLBACK_REGEX;
      }
    }
    g_error_free(error);
    error = NULL;
  }

  std::string text;

  if ( opt_file != NULL ) {
    text = read_file(opt_file);
  } else {
    text = read_stdin();
  }

  if ( ! text.empty() &&  ! regex_pattern.empty() )
    parse_text(text, regex_pattern);

  main_cleanup();

  return(EXIT_SUCCESS);
}

