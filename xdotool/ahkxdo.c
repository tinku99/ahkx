/*
AutoHotkeyX 

Copyright 2003-2009 Naveen Garg (naveen.garg@gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE 1
#define __USE_BSD /* for strdup on linux/glibc */
#include <getopt.h>
#include <string.h>
#include <strings.h>
#include "xdo.h"
#include "ahkxdo.h"

static xdo_t *xdo; 
void init();
int mousemove(int x, int y, int relative);

void init()
{
  xdo = xdo_new(getenv("DISPLAY"));
}

int mousemove(int x, int y, int relative)
{
  if (relative)
    return xdo_mousemove_relative(xdo, x, y);
  else
    return xdo_mousemove(xdo, x, y);

}
int mouseclick(int x, int y, int button, int updown);

int mouseclick(int x, int y, int button, int updown)
{
  mousemove(x, y, 0);
  if (updown == 0)
    return xdo_mousedown(xdo, button);
  if (updown == 1)
    return xdo_mouseup(xdo, button);

}


int mousegetpos(int x, int y, int screen_num);
int mousegetpos(int x, int y, int screen_num) // todo: fix me
{
  return xdo_mouselocation(xdo, &x, &y, &screen_num);

}

