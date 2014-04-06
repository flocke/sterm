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

#ifndef _STERM_FUNCTIONS_H
#define _STERM_FUNCTIONS_H

#include "terminal.h"

typedef struct {
  gchar *name;
  void *callback;
} STermFunction;

void initialize_functions ( STermTerminal *sterm );

#endif
