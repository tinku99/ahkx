/* $XConsortium: xev.c,v 1.15 94/04/17 20:45:20 keith Exp $ */
/*

Copyright (c) 1988  X Consortium

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from the X Consortium.

*/
/* $XFree86: xc/programs/xev/xev.c,v 1.13 2003/10/24 20:38:17 tsi Exp $ */

/*
 * Author:  Jim Fulton, MIT X Consortium
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <X11/Xlocale.h>
#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xproto.h>

#define INNER_WINDOW_WIDTH 50
#define INNER_WINDOW_HEIGHT 50
#define INNER_WINDOW_BORDER 4
#define INNER_WINDOW_X 10
#define INNER_WINDOW_Y 10
#define OUTER_WINDOW_MIN_WIDTH (INNER_WINDOW_WIDTH + \
				2 * (INNER_WINDOW_BORDER + INNER_WINDOW_X))
#define OUTER_WINDOW_MIN_HEIGHT (INNER_WINDOW_HEIGHT + \
				2 * (INNER_WINDOW_BORDER + INNER_WINDOW_Y))
#define OUTER_WINDOW_DEF_WIDTH (OUTER_WINDOW_MIN_WIDTH + 100)
#define OUTER_WINDOW_DEF_HEIGHT (OUTER_WINDOW_MIN_HEIGHT + 100)
#define OUTER_WINDOW_DEF_X 100
#define OUTER_WINDOW_DEF_Y 100
				

typedef unsigned long Pixel;
