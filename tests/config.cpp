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
#include <string>
#include <vector>

#include <vte/vte.h>

#include "sterm/config.hpp"

int main(int argc, char **argv) {
  bool success = true;

  std::string encoding_should = "ISO-8859-15";

  std::vector<std::string> palette_colors = {
    "#1b1d1e", "#f92672", "#82b414", "#fd971f",
    "#56c2d6", "#8c54fe", "#465457", "#ccccc6",
    "#505354", "#ff5995", "#b6e354", "#feed6c",
    "#8cedff", "#9e6ffe", "#899ca1", "#f8f8f2"
  };

  std::string font_name = "Inconsolata 10";

  sterm::config conf(argv[1]);

  gint scrollback_lines = conf.get_scrollback_lines();
  gboolean allow_bold = conf.get_allow_bold();
  gboolean audible_bell = conf.get_audible_bell();
  gboolean urgent_on_bell = conf.get_urgent_on_bell();
  gboolean scroll_on_keystroke = conf.get_scroll_on_keystroke();
  gboolean scroll_on_output = conf.get_scroll_on_output();
  gboolean rewrap_on_resize = conf.get_rewrap_on_resize();
  gboolean autohide_mouse = conf.get_autohide_mouse();
  std::string encoding_is = conf.get_encoding();

  VteCursorBlinkMode cursor_blink_mode = conf.get_cursor_blink_mode();
  VteCursorShape cursor_shape = conf.get_cursor_shape();

  sterm::color foreground = conf.get_foreground_color();
  sterm::color background = conf.get_background_color();

  std::vector<GdkRGBA> palette = conf.get_color_palette();

  if ( scrollback_lines != 1000 ) {
    std::cout << "Fail: scrollback is not 1000" << std::endl;
    success = false;
  }

  if ( allow_bold != false ) {
    std::cout << "Fail: allow_bold is not false" << std::endl;
    success = false;
  }

  if ( audible_bell != true ) {
    std::cout << "Fail: audible_bell is not true" << std::endl;
    success = false;
  }

  if ( urgent_on_bell != false ) {
    std::cout << "Fail: urgent_on_bell is not false" << std::endl;
    success = false;
  }

  if ( scroll_on_keystroke != false ) {
    std::cout << "Fail: scroll_on_keystroke is not false" << std::endl;
    success = false;
  }

  if ( scroll_on_output != true ) {
    std::cout << "Fail: scroll_on_output is not true" << std::endl;
    success = false;
  }

  if ( rewrap_on_resize != true ) {
    std::cout << "Fail: rewrap_on_resize is not true" << std::endl;
    success = false;
  }
  
  if ( autohide_mouse != true ) {
    std::cout << "Fail: autohide_mouse is not true" << std::endl;
    success = false;
  }

  if ( encoding_is.compare(encoding_should) != 0 ) {
    std::cout << "Fail: encoding is not " << encoding_should << std::endl;
    success = false;
  }

  if ( cursor_blink_mode != VTE_CURSOR_BLINK_OFF ) {
    std::cout << "Fail: blink_mode is not VTE_CURSOR_BLINK_OFF" << std::endl;
    success = false;
  }

  if ( cursor_shape != VTE_CURSOR_SHAPE_UNDERLINE ) {
    std::cout << "Fail: shape is not VTE_CURSOR_SHAPE_UNDERLINE" << std::endl;
    success = false;
  }

  if ( foreground.set ) {
    GdkRGBA temp;
    gdk_rgba_parse( &temp, "#a0a0a0" );

    if ( ! gdk_rgba_equal( &temp, &(foreground.value) ) ) {
      std::cout << "Fail: foreground color is not #a0a0a0" << std::endl;
      success = false;
    }
  } else {
    std::cout << "Fail: foreground color not set" << std::endl;
    success = false;
  }

  if ( background.set ) {
    GdkRGBA temp;
    gdk_rgba_parse( &temp, "#1b1d1e" );

    if ( ! gdk_rgba_equal(&temp, &(background.value)) ) {
      std::cout << "Fail: background color is not #1b1d1e" << std::endl;
      success = false;
    }
  } else {
    std::cout << "Fail: background color not set" << std::endl;
    success = false;
  }

  if ( palette.size() == PALETTE_SIZE ) {
    for ( int i = 0; i < PALETTE_SIZE; i++ ) {
      GdkRGBA is, should;
      is = palette[i];
      gdk_rgba_parse(&should, palette_colors[i].c_str());

      if ( ! gdk_rgba_equal(&is, &should) ) {
        std::cout << "Fail: color " << i << " in the palette is not " << palette_colors[i] << std::endl;
        success = false;
      }
    }
  } else {
    std::cout << "Fail: color palette has the wrong size" << std::endl;
    success = false;
  }

  PangoFontDescription *font_is = NULL;

  if ( conf.copy_font_description(&font_is) ) {
    PangoFontDescription *font_should = pango_font_description_from_string(font_name.c_str());

    if ( ! pango_font_description_equal(font_is, font_should) ) {
      std::cout << "Fail: font is not " << font_name << std::endl;
      success = false;
    }

    pango_font_description_free(font_is);
    pango_font_description_free(font_should);
  } else {
    std::cout << "Fail: font is not set" << std::endl;
    success = false;
  }

  if ( success )
    return(EXIT_SUCCESS);
  else
    return(EXIT_FAILURE);
}

