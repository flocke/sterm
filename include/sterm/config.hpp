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

#ifndef __STERM_CONFIG_HPP
#define __STERM_CONFIG_HPP

#define PALETTE_SIZE 16

#include <string>
#include <vector>

#include <vte/vte.h>

namespace sterm {

  struct color {
    GdkRGBA               value;
    bool                  set;
    color() { set = false; }
  };

  struct keysym {
    GdkModifierType modifier;
    guint keyval;
    std::string function;

    keysym() { modifier = (GdkModifierType) 0; }
  };

  class config {
    private:
      gint                    m_scrollback_lines = 0;
      gboolean                m_allow_bold = true;
      gboolean                m_audible_bell = false;
      gboolean                m_urgent_on_bell = true;
      gboolean                m_scroll_on_keystroke = true;
      gboolean                m_scroll_on_output = false;
      gboolean                m_rewrap_on_resize = false;
      gboolean                m_autohide_mouse = false;
      std::string             m_encoding = "UTF-8";

      VteCursorBlinkMode      m_cursor_blink_mode = VTE_CURSOR_BLINK_SYSTEM;
      VteCursorShape          m_cursor_shape = VTE_CURSOR_SHAPE_BLOCK;

      color                   m_foreground_color;
      color                   m_background_color;

      std::vector<GdkRGBA>    m_color_palette;

      PangoFontDescription   *m_font = NULL;

      std::vector<keysym>     m_keys;

      bool                    inifile_read_string(GKeyFile *keyfile, std::string section, std::string key, std::string *target);
      bool                    inifile_read_gboolean(GKeyFile *keyfile, std::string section, std::string key, gboolean *target);
      bool                    inifile_read_gint(GKeyFile *keyfile, std::string section, std::string key, gint *target);

      bool                    inifile_read_cursor_shape(GKeyFile *keyfile, std::string section, std::string key, VteCursorShape *target);
      bool                    inifile_read_cursor_blink_mode(GKeyFile *keyfile, std::string section, std::string key, VteCursorBlinkMode *target);

      bool                    inifile_parse_color(GKeyFile *keyfile, std::string section, std::string key, color *target);
      bool                    inifile_parse_color_palette(GKeyFile *keyfile, std::string section, std::string prefix, std::vector<GdkRGBA> *target);

      bool                    inifile_parse_font(GKeyFile *keyfile, std::string section, std::string key, PangoFontDescription **target);

      bool                    inifile_parse_keys(GKeyFile *keyfile, std::string section, std::vector<keysym> *target);

    public:
      config();
      config(std::string filename);
      ~config();

      void                    load_from_inifile(std::string filename);

      gint                    get_scrollback_lines() const { return(m_scrollback_lines); }
      gboolean                get_allow_bold() const { return(m_allow_bold); }
      gboolean                get_audible_bell() const { return(m_audible_bell); }
      gboolean                get_urgent_on_bell() const { return(m_urgent_on_bell); }
      gboolean                get_scroll_on_keystroke() const { return(m_scroll_on_keystroke); }
      gboolean                get_scroll_on_output() const { return(m_scroll_on_output); }
      gboolean                get_rewrap_on_resize() const { return(m_rewrap_on_resize); }
      gboolean                get_autohide_mouse() const { return(m_autohide_mouse); }
      std::string             get_encoding() const { return(m_encoding); }

      VteCursorBlinkMode      get_cursor_blink_mode() const { return(m_cursor_blink_mode); }
      VteCursorShape          get_cursor_shape() const { return(m_cursor_shape); }

      color                   get_foreground_color() const { return(m_foreground_color); }
      color                   get_background_color() const { return(m_background_color); }

      std::vector<GdkRGBA>    get_color_palette() const { return(m_color_palette); }

      bool                    copy_font_description(PangoFontDescription **target);

      std::vector<keysym>     get_keys() const { return(m_keys); }

  };

}

#endif
