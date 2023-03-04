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

#ifndef __STERM_TERMINAL_HPP
#define __STERM_TERMINAL_HPP

#include <string>

#include <vte/vte.h>

#include "sterm/config.hpp"

namespace sterm {

  enum paste_buffer {
    PRIMARY,
    CLIPBOARD
  };

  class terminal {
    private:
      config       *m_configuration = NULL;
      VteTerminal  *m_terminal = NULL;
      GtkWidget    *m_terminal_widget = NULL;
      GtkContainer *m_container = NULL;
      GPid          m_child_pid;

      bool          setup = false;

      void          create_vte_terminal();

    public:
                    terminal();
                    terminal(config *configuration);
                    ~terminal();

      void          set_configuration(config *configuration);
      void          setup_terminal();

      void          attach_to_container(GtkContainer *container);

      void          connect_callback(std::string type, GCallback callback, void *argument);

      void          link_property_to_terminal(std::string terminal_property, GObject *target, std::string target_property);

      void          spawn_child(std::string command);
      void          set_child_pid(GPid pid);

      void          reload_configuration();
      void          reset_terminal(gboolean full);

      std::string   get_window_title();
      std::string   get_text();
      gdouble       get_font_scale();

      void          set_font_scale(double font_scale);
      void          set_font_description(PangoFontDescription **font);
      void          insert_text(std::string text);
      void          paste(paste_buffer buffer);
  };

}

#endif
