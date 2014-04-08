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

#ifndef DEFAULT_CURSOR_SHAPE
#define DEFAULT_CURSOR_SHAPE VTE_CURSOR_SHAPE_BLOCK
#endif

#ifndef DEFAULT_CURSOR_BLINK
#define DEFAULT_CURSOR_BLINK VTE_CURSOR_BLINK_SYSTEM
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

#ifndef DEFAULT_COLOR_COLOR0
#define DEFAULT_COLOR_COLOR0 "#1b1d1e"
#endif

#ifndef DEFAULT_COLOR_COLOR1
#define DEFAULT_COLOR_COLOR1 "#f92672"
#endif

#ifndef DEFAULT_COLOR_COLOR2
#define DEFAULT_COLOR_COLOR2 "#82b414"
#endif

#ifndef DEFAULT_COLOR_COLOR3
#define DEFAULT_COLOR_COLOR3 "#fd971f"
#endif

#ifndef DEFAULT_COLOR_COLOR4
#define DEFAULT_COLOR_COLOR4 "#56c2d6"
#endif

#ifndef DEFAULT_COLOR_COLOR5
#define DEFAULT_COLOR_COLOR5 "#8c54fe"
#endif

#ifndef DEFAULT_COLOR_COLOR6
#define DEFAULT_COLOR_COLOR6 "#465457"
#endif

#ifndef DEFAULT_COLOR_COLOR7
#define DEFAULT_COLOR_COLOR7 "#ccccc6"
#endif

#ifndef DEFAULT_COLOR_COLOR8
#define DEFAULT_COLOR_COLOR8 "#505354"
#endif

#ifndef DEFAULT_COLOR_COLOR9
#define DEFAULT_COLOR_COLOR9 "#ff5995"
#endif

#ifndef DEFAULT_COLOR_COLOR10
#define DEFAULT_COLOR_COLOR10 "#b6e354"
#endif

#ifndef DEFAULT_COLOR_COLOR11
#define DEFAULT_COLOR_COLOR11 "#feed6c"
#endif

#ifndef DEFAULT_COLOR_COLOR12
#define DEFAULT_COLOR_COLOR12 "#8cedff"
#endif

#ifndef DEFAULT_COLOR_COLOR13
#define DEFAULT_COLOR_COLOR13 "#9e6ffe"
#endif

#ifndef DEFAULT_COLOR_COLOR14
#define DEFAULT_COLOR_COLOR14 "#899ca1"
#endif

#ifndef DEFAULT_COLOR_COLOR15
#define DEFAULT_COLOR_COLOR15 "#f8f8f2"
#endif

#endif
