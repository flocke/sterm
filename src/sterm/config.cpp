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

#include "common/strsplit.hpp"
#include "sterm/config.hpp"

namespace sterm {

  config::config() {}

  config::config(std::string i_filename) {
    this->load_from_inifile(i_filename);
  }

  config::~config() {
    if ( ! m_color_palette.empty() )
      m_color_palette.clear();

    if ( ! m_keys.empty() )
      m_keys.clear();

    if ( m_font != NULL )
      pango_font_description_free(m_font);
  }

  bool config::inifile_read_string(GKeyFile *i_keyfile, std::string i_section, std::string i_key, std::string *target) {
    if ( i_keyfile != NULL ) {
      GError *error = NULL;

      gchar *value = g_key_file_get_string(i_keyfile, i_section.c_str(), i_key.c_str(), &error);

      if ( error == NULL ) {
        *target = value;
        g_free(value);
        return(true);
      }
      
      g_error_free(error);
    }

    return(false);
  }

  bool config::inifile_read_gboolean(GKeyFile *i_keyfile, std::string i_section, std::string i_key, gboolean *target) {
    if ( i_keyfile != NULL ) {
      GError *error = NULL;

      gboolean value = g_key_file_get_boolean(i_keyfile, i_section.c_str(), i_key.c_str(), &error);

      if( error == NULL ) {
        *target = value;
        return(true);
      }

      g_error_free(error);
    }

    return(false);
  }

  bool config::inifile_read_gint(GKeyFile *i_keyfile, std::string i_section, std::string i_key, gint *target) {
    if ( i_keyfile != NULL ) {
      GError *error = NULL;

      gint value = g_key_file_get_integer(i_keyfile, i_section.c_str(), i_key.c_str(), &error);

      if ( error == NULL ) {
        *target = value;
        return(true);
      }
      
      g_error_free(error);
    }

    return(false);
  }

  bool config::inifile_read_cursor_shape(GKeyFile *i_keyfile, std::string i_section, std::string i_key, VteCursorShape *i_target) {
    if ( i_keyfile != NULL ) {
      std::string temp;

      if ( this->inifile_read_string(i_keyfile, i_section, i_key , &temp) ) {

        if ( temp.compare("block") == 0 ) {
          *i_target = VTE_CURSOR_SHAPE_BLOCK;
        } else if ( temp.compare("beam") == 0 ) {
          *i_target = VTE_CURSOR_SHAPE_IBEAM;
        } else if ( temp.compare("underline") == 0 ) {
          *i_target = VTE_CURSOR_SHAPE_UNDERLINE;
        } else {
          return(false);
        }

        return(true);
      }
    }

    return(false);
  }

  bool config::inifile_read_cursor_blink_mode(GKeyFile *i_keyfile, std::string i_section, std::string i_key, VteCursorBlinkMode *i_target) {
    if ( i_keyfile != NULL ) {
      std::string temp;

      if ( this->inifile_read_string(i_keyfile, i_section, i_key, &temp) ) {

        if ( temp.compare("on") == 0 ) {
          *i_target = VTE_CURSOR_BLINK_ON;
        } else if ( temp.compare("off") == 0 ) {
          *i_target = VTE_CURSOR_BLINK_OFF;
        } else if ( temp.compare("system") == 0 ) {
          *i_target = VTE_CURSOR_BLINK_SYSTEM;
        } else {
          return(false);
        }

        return(true);
      }
    }

    return(false);
  }

  bool config::inifile_parse_color(GKeyFile *i_keyfile, std::string i_section, std::string i_key, color *i_target) {
    if ( i_keyfile != NULL ) {
      std::string temp;

      i_target->set = false;

      if ( this->inifile_read_string(i_keyfile, i_section, i_key, &temp) )
        if ( gdk_rgba_parse(&(i_target->value), temp.c_str()) ) {
          i_target->set = true;

          return(true);
        }
    }

    return(false);
  }

  bool config::inifile_parse_color_palette(GKeyFile *i_keyfile, std::string i_section, std::string i_prefix, std::vector<GdkRGBA> *i_target) {
    if ( i_keyfile != NULL ) {
      if ( ! i_target->empty() )
        i_target->clear();

      for ( int i = 0; i < PALETTE_SIZE; i++ ) {
        color temp;
        
        std::string key = i_prefix + std::to_string(i);
        if ( this->inifile_parse_color(i_keyfile, i_section, key.c_str(), &temp) )
          i_target->push_back(temp.value);
      }

      if ( i_target->size() != PALETTE_SIZE ) {
        i_target->clear();
        g_warning("color palette not complete, falling back on the default colors");

        return(false);
      }

      return(true);
    }
    
    return(false);
  }

  bool config::inifile_parse_font(GKeyFile *i_keyfile, std::string i_section, std::string i_key, PangoFontDescription **i_target) {
    if ( i_keyfile != NULL ) {
      std::string temp;

      if ( *i_target != NULL )
        pango_font_description_free(*i_target);

      if ( this->inifile_read_string(i_keyfile, i_section, i_key, &temp) )
        *i_target = pango_font_description_from_string(temp.c_str());
      else
        *i_target = pango_font_description_from_string(DEFAULT_FONT);

      if ( *i_target != NULL )
        return(true);
    }

    return(false);
  }

  bool config::inifile_parse_keys(GKeyFile *i_keyfile, std::string i_section, std::vector<keysym> *i_target) {
    if ( i_keyfile != NULL ) {
      GError *error = NULL;

      gsize length = 0;
      gchar **keys = g_key_file_get_keys(i_keyfile, i_section.c_str(), &length, &error);

      if ( error == NULL ) {
        if ( ! i_target->empty() )
          i_target->clear();

        for ( int iter = 0; iter < length; iter++ ) {
          keysym key;

          std::vector<std::string> parts = sterm::common::strsplit(std::string(keys[iter]), '-');

          bool add = true;

          for ( int i = 0; i < parts.size() - 1; i++ ) {
            if ( parts[i].compare("Mod1") == 0 ) {
              key.modifier = (GdkModifierType) ( key.modifier | GDK_MOD1_MASK );
            } else if ( parts[i].compare("Control") == 0 ) {
              key.modifier = (GdkModifierType) ( key.modifier | GDK_CONTROL_MASK );
            } else if ( parts[i].compare("Shift") == 0 ) {
              key.modifier = (GdkModifierType) ( key.modifier | GDK_SHIFT_MASK );
            } else {
              g_warning("invalid key modifier: %s", parts[i]);
              add = false;
            }
          }

          key.keyval = gdk_keyval_from_name(parts.back().c_str());

          if ( key.keyval == GDK_KEY_VoidSymbol ) {
            g_warning("invalid key: %s", parts.back());
            add = false;
          }

          if ( this->inifile_read_string(i_keyfile, i_section, keys[iter], &key.function) )
            if ( add )
              i_target->push_back(key);
        }

        g_strfreev(keys);

        return(true);
      } else {
        g_error_free(error);
      }
    }

    return(false);
  }

  void config::load_from_inifile(std::string i_filename) {
    GError *error = NULL;

    GKeyFile *keyfile = g_key_file_new();
    g_key_file_load_from_file(keyfile, i_filename.c_str(), G_KEY_FILE_NONE, &error);

    if ( error != NULL ) {
      keyfile = NULL;
      g_error_free(error);

      return;
    }

    m_current_file = i_filename;

    this->inifile_read_gint(keyfile, "general", "scrollback", &m_scrollback_lines);
    this->inifile_read_gboolean(keyfile, "general", "allow_bold", &m_allow_bold);
    this->inifile_read_gboolean(keyfile, "general", "audible_bell", &m_audible_bell);
    this->inifile_read_gboolean(keyfile, "general", "urgent_on_bell", &m_urgent_on_bell);
    this->inifile_read_gboolean(keyfile, "general", "scroll_on_keystroke", &m_scroll_on_keystroke);
    this->inifile_read_gboolean(keyfile, "general", "scroll_on_output", &m_scroll_on_output);
    this->inifile_read_gboolean(keyfile, "general", "rewrap_on_resize", &m_rewrap_on_resize);
    this->inifile_read_gboolean(keyfile, "general", "autohide_mouse", &m_autohide_mouse);
    this->inifile_read_string(keyfile, "general", "encoding", &m_encoding);

    this->inifile_read_cursor_shape(keyfile, "cursor", "shape", &m_cursor_shape);
    this->inifile_read_cursor_blink_mode(keyfile, "cursor", "blink", &m_cursor_blink_mode);

    this->inifile_parse_color(keyfile, "theme", "foreground", &m_foreground_color);
    this->inifile_parse_color(keyfile, "theme", "background", &m_background_color);

    this->inifile_parse_color_palette(keyfile, "theme", "color", &m_color_palette);

    this->inifile_parse_font(keyfile, "theme", "font", &m_font);

    this->inifile_parse_keys(keyfile, "keys", &m_keys);

    if ( keyfile != NULL ) {
      g_key_file_free(keyfile);
    }
  }

  void config::reload_inifile() {
    if ( ! m_current_file.empty() )
      this->load_from_inifile(m_current_file);
  }

  bool config::copy_font_description(PangoFontDescription **i_target) {
    if ( m_font != NULL ) {
      *i_target = pango_font_description_copy(m_font);
      return(true);
    }

    return(false);
  }

  bool config::get_key_function(guint i_keyval, guint i_modifiers, std::string *i_target) {
    if ( ! m_keys.empty() )
      for ( int iter = 0; iter < m_keys.size(); iter++ )
        if ( ( i_modifiers & ( m_keys[iter].modifier ) ) == ( m_keys[iter].modifier ) )
          if ( i_keyval == m_keys[iter].keyval ) {
            *i_target = m_keys[iter].function;
            return(true);
          }

    return(false);
  }

}

