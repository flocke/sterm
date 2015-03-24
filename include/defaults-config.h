/*
  Copyright (c) 2014-2015 Jakob Nixdorf <flocke@shadowice.org>

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

#ifndef _STERM_DEFAULTS_CONFIG_H
#define _STERM_DEFAULTS_CONFIG_H

#define DEFAULT_PALETTE_SIZE 16

#ifndef DEFAULT_SCROLLBACK_LINES
#define DEFAULT_SCROLLBACK_LINES 0
#endif

#ifndef DEFAULT_ALLOW_BOLD
#define DEFAULT_ALLOW_BOLD TRUE
#endif

#ifndef DEFAULT_AUDIBLE_BELL
#define DEFAULT_AUDIBLE_BELL FALSE
#endif

#ifndef DEFAULT_VISIBLE_BELL
#define DEFAULT_VISIBLE_BELL TRUE
#endif

#ifndef DEFAULT_SCROLL_ON_KEYSTROKE
#define DEFAULT_SCROLL_ON_KEYSTROKE TRUE
#endif

#ifndef DEFAULT_SCROLL_ON_OUTPUT
#define DEFAULT_SCROLL_ON_OUTPUT FALSE
#endif

#ifndef DEFAULT_REWRAP_ON_RESIZE
#define DEFAULT_REWRAP_ON_RESIZE FALSE
#endif

#ifndef DEFAULT_MOUSE_AUTOHIDE
#define DEFAULT_MOUSE_AUTOHIDE FALSE
#endif

// #ifndef DEFAULT_WORD_CHAR_EXCEPTIONS
// #define DEFAULT_WORD_CHAR_EXCEPTIONS NULL
// #endif

#ifndef DEFAULT_ENCODING
#define DEFAULT_ENCODING "UTF-8"
#endif

#ifndef DEFAULT_CURSOR_SHAPE
#define DEFAULT_CURSOR_SHAPE "block"
#endif

#ifndef DEFAULT_CURSOR_BLINK
#define DEFAULT_CURSOR_BLINK "system"
#endif

#ifndef DEFAULT_FONT
#define DEFAULT_FONT "monospace 10"
#endif

#ifndef DEFAULT_COLOR_BACKGROUND
#define DEFAULT_COLOR_BACKGROUND "#000000"
#endif

#ifndef DEFAULT_COLOR_FOREGROUND
#define DEFAULT_COLOR_FOREGROUND "#c0c0c0"
#endif

#ifndef DEFAULT_COLOR_PALETTE
#define DEFAULT_COLOR_PALETTE "#1b1d1e #f92672 #82b414 #fd971f #56c2d6 #8c54fe #465457 #ccccc6 #505354 #ff5995 #b6e354 #feed6c #8cedff #9e6ffe #899ca1 #f8f8f2"
#endif

#endif
