/*
  This file is part of STerm.

  STerm is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  STerm is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with STerm.  If not, see <http://www.gnu.org/licenses/>.
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

#ifndef DEFAULT_WORD_CHARS
#define DEFAULT_WORD_CHARS "-A-Za-z0-9,./?%&#:_"
#endif

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
