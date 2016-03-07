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

#include "sterm/terminal.hpp"

namespace sterm {

  terminal::terminal() {
    this->create_vte_terminal();
  }

  terminal::terminal(config *i_configuration) {
    this->create_vte_terminal();
    this->set_configuration(i_configuration);
  }

  terminal::~terminal() {
    if ( m_terminal_widget != NULL )
      gtk_widget_destroy(m_terminal_widget);
  }

  void terminal::create_vte_terminal() {
    if ( m_terminal_widget == NULL ) {
      m_terminal_widget = vte_terminal_new();
      m_terminal = VTE_TERMINAL( m_terminal_widget );

      g_signal_connect(G_OBJECT(m_terminal_widget), "destroy", G_CALLBACK(gtk_widget_destroyed), &m_terminal_widget);
    }

    if ( m_configuration != NULL )
      this->setup_terminal();
  }

  void terminal::set_configuration(config *i_configuration) {
    if ( i_configuration != NULL ) {
      m_configuration = i_configuration;
      if ( m_terminal != NULL )
        this->setup_terminal();
    }
  }

  void terminal::setup_terminal() {
    if ( m_terminal && m_configuration ) {
      GError *error = NULL;

      vte_terminal_set_scrollback_lines(m_terminal, m_configuration->get_scrollback_lines());
      vte_terminal_set_allow_bold(m_terminal, m_configuration->get_allow_bold());
      vte_terminal_set_audible_bell(m_terminal, m_configuration->get_audible_bell());
      vte_terminal_set_scroll_on_keystroke(m_terminal, m_configuration->get_scroll_on_keystroke());
      vte_terminal_set_scroll_on_output(m_terminal, m_configuration->get_scroll_on_output());
      vte_terminal_set_rewrap_on_resize(m_terminal, m_configuration->get_rewrap_on_resize());
      vte_terminal_set_mouse_autohide(m_terminal, m_configuration->get_autohide_mouse());
      if ( ! vte_terminal_set_encoding(m_terminal, m_configuration->get_encoding().c_str(), &error) )
        g_warning("Failed to set the terminal encoding: %s", error->message);

      std::string word_chars = m_configuration->get_word_chars();
      if ( ! word_chars.empty() )
        vte_terminal_set_word_char_exceptions(m_terminal, word_chars.c_str());
      else
        vte_terminal_set_word_char_exceptions(m_terminal, NULL);

      vte_terminal_set_cursor_blink_mode(m_terminal, m_configuration->get_cursor_blink_mode());
      vte_terminal_set_cursor_shape(m_terminal, m_configuration->get_cursor_shape());

      PangoFontDescription *font = NULL;
      if ( m_configuration->copy_font_description(&font) ) {
        vte_terminal_set_font(m_terminal, font);
        pango_font_description_free(font);
      } else {
        vte_terminal_set_font(m_terminal, NULL);
      }

      std::vector<GdkRGBA> color_palette = m_configuration->get_color_palette();
      color foreground = m_configuration->get_foreground_color();
      color background = m_configuration->get_background_color();
      color bold_color = m_configuration->get_bold_color();
      color cursor_color = m_configuration->get_cursor_color();
      color highlight_bg = m_configuration->get_highlight_bg_color();
      color highlight_fg = m_configuration->get_highlight_fg_color();

      if ( color_palette.size() == PALETTE_SIZE )
        vte_terminal_set_colors(m_terminal, NULL, NULL, color_palette.data(), PALETTE_SIZE);
      else
        vte_terminal_set_default_colors(m_terminal);

      if ( foreground.set )
        vte_terminal_set_color_foreground(m_terminal, &(foreground.value));

      if ( background.set )
        vte_terminal_set_color_background(m_terminal, &(background.value));

      if ( bold_color.set )
        vte_terminal_set_color_bold(m_terminal, &(bold_color.value));
      else
        vte_terminal_set_color_bold(m_terminal, NULL);

      if ( cursor_color.set )
        vte_terminal_set_color_cursor(m_terminal, &(cursor_color.value));
      else
        vte_terminal_set_color_cursor(m_terminal, NULL);

      if ( highlight_bg.set )
        vte_terminal_set_color_highlight(m_terminal, &(highlight_bg.value));
      else
        vte_terminal_set_color_highlight(m_terminal, NULL);

      if ( highlight_fg.set )
        vte_terminal_set_color_highlight_foreground(m_terminal, &(highlight_fg.value));
      else
        vte_terminal_set_color_highlight_foreground(m_terminal, NULL);
    }
  }

  void terminal::spawn_child(std::string i_command) {
    if ( m_terminal != NULL ) {
      GError *error = NULL;
      gchar **args = NULL;
      GSpawnFlags spawn_flags = G_SPAWN_SEARCH_PATH;

      if ( i_command.empty() ) {
        gchar *user_shell = vte_get_user_shell();

        g_shell_parse_argv(user_shell, 0, &args, 0);

        g_free(user_shell);
      } else {
        g_shell_parse_argv(i_command.c_str(), 0, &args, 0);
      }

      vte_terminal_spawn_sync(m_terminal, VTE_PTY_DEFAULT, NULL, args, NULL, spawn_flags, NULL, NULL, &m_child_pid, NULL, &error);

      if ( error != NULL ) {
        g_warning("failed to spawn child process: %s", error->message);
        g_error_free(error);
      }
      
      g_strfreev(args);
    }
  }

  void terminal::attach_to_container(GtkContainer *i_container) {
    if ( i_container != NULL && m_terminal_widget != NULL ) {
      gtk_container_add(i_container, m_terminal_widget);
      m_container = i_container;
    }
  }

  void terminal::connect_callback(std::string i_type, GCallback i_callback, void *argument) {
    if ( m_terminal_widget != NULL )
      if ( i_callback != NULL && ! i_type.empty() )
        g_signal_connect(G_OBJECT(m_terminal_widget), i_type.c_str(), i_callback, argument);
  }

  void terminal::link_property_to_terminal(std::string i_terminal_property, GObject *i_target, std::string i_target_property) {
    if ( m_terminal != NULL && i_target != NULL )
      g_object_bind_property(G_OBJECT(m_terminal_widget), i_terminal_property.c_str(), i_target, i_target_property.c_str(), G_BINDING_DEFAULT);
  }

  void terminal::reload_configuration() {
    if ( m_configuration != NULL ) {
      m_configuration->reload_inifile();
      this->setup_terminal();
    }
  }

  void terminal::reset_terminal(gboolean i_full) {
    if ( m_terminal != NULL )
      vte_terminal_reset(m_terminal, i_full, i_full);
  }

  std::string terminal::get_window_title() {
    std::string title;

    if ( m_terminal != NULL )
      title = vte_terminal_get_window_title(m_terminal);

    return(title);
  }

  std::string terminal::get_text() {
    std::string text;

    if ( m_terminal != NULL )
      text = vte_terminal_get_text(m_terminal, NULL, NULL, NULL);

    return(text);
  }

  gdouble terminal::get_font_scale() {
    if ( m_terminal != NULL )
      return(vte_terminal_get_font_scale(m_terminal));
  }

  void terminal::set_font_scale(double i_font_scale) {
    if ( m_terminal != NULL && i_font_scale > 0 )
      vte_terminal_set_font_scale(m_terminal, i_font_scale);
  }

  void terminal::set_font_description(PangoFontDescription **i_font) {
    if ( m_terminal != NULL && *i_font != NULL ) {
      vte_terminal_set_font(m_terminal, *i_font);
    }
  }

  void terminal::insert_text(std::string i_text) {
    if ( m_terminal != NULL ) {
      vte_terminal_feed_child(m_terminal, i_text.c_str(), -1);
    }
  }

  void terminal::paste(paste_buffer i_buffer) {
    if ( m_terminal != NULL ) {
      if ( i_buffer == PRIMARY )
        vte_terminal_paste_primary(m_terminal);
      else if ( i_buffer == CLIPBOARD )
        vte_terminal_paste_clipboard(m_terminal);
    }
  }

}

