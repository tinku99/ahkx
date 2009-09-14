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
extern void window_print(Window wid);
void init(void);

int mousemove(int x, int y, int relative);
int mouseclick(int x, int y, int button, int updown);
int mousegetpos(int *x, int *y, int *screen_num);

Window wingetid(char *rgxname);
unsigned int wingettitle(void);
int winrestore(char *rgxname);
int winactivate(char *rgxname);
int winmove(char *rgxname, int x, int y);
int ifwinactive(char *rgxname); 
void init(void)
{
  xdo = xdo_new(getenv("DISPLAY"));
  return ;
}

int mousemove(int x, int y, int relative)
{
  if (relative)
    return xdo_mousemove_relative(xdo, x, y);
  else
    return xdo_mousemove(xdo, x, y);

}


int mouseclick(int x, int y, int button, int updown)
{
  mousemove(x, y, 0);
  if (updown == 0)
    xdo_click(xdo, button);
  else if (updown == 1)
    xdo_mousedown(xdo, button);
  else if (updown == 2)
    xdo_mouseup(xdo, button);
  return 0;
}



int mousegetpos(int *x, int *y, int *screen_num) // todo: fix screen_num
{
  return xdo_mouselocation(xdo, x, y, screen_num);
}

unsigned int wingettitle(void)
{
  Window wid;
  xdo_window_get_active(xdo, &wid);
  return wid;
}

int winrestore(char *rgxname)
{

 Window wid = wingetid(rgxname);
 xdo_window_raise(xdo, wid);
 return 0;
}

int winactivate(char *rgxname)
{

 Window list = wingetid(rgxname);
 xdo_window_activate(xdo, list);
 return 0;
}

int winmove(char *rgxname, int x, int y)
{

 Window list = wingetid(rgxname);
 xdo_window_move(xdo, list, x, y);
 return 0;
}



Window wingetid(char *rgxname)
{
  Window wid;
  Window *list;  // window = unsigned long
  int nwindows;
  int i;
  int max_depth = -1;
  int search_flags = 0;
  search_flags |= SEARCH_VISIBLEONLY;
  search_flags |= SEARCH_TITLE;
  search_flags |= SEARCH_NAME;
  search_flags |= SEARCH_CLASS;

  xdo_window_list_by_regex(xdo, rgxname, search_flags, max_depth, &list, &nwindows);
  for (i = 0; i < nwindows; i++)
    window_print(list[i]);

  wid = list[0];
  /* Free list as it's malloc'd by xdo_window_list_by_regex */
  free(list);
  return wid;   // remember to free(list);
}

int ifwinactive(char *rgxname)
{
  Window cid = wingettitle(); 
  Window wid = wingetid(rgxname);
  if (cid == wid)
    return 1;
  else
    return NULL; 
}
