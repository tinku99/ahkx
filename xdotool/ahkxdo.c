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
int send(char *message, char *rgxname);

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
  // printf("in wingetid with %s", rgxname);
  Window wid = 0;
  Window *list;  // window = unsigned long
  int nwindows;
  //  int i;
  int max_depth = -1;
  int search_flags = 0;
  search_flags |= SEARCH_VISIBLEONLY;
  search_flags |= SEARCH_TITLE;
  search_flags |= SEARCH_NAME;
  search_flags |= SEARCH_CLASS;

  xdo_window_list_by_regex(xdo, rgxname, search_flags, max_depth, &list, &nwindows);
  //  for (i = 0; i < nwindows; i++)
  //    window_print(list[i]);

  wid = list[0];
  /* Free list as it's malloc'd by xdo_window_list_by_regex */
  free(list);
  if (nwindows > 0)
    return wid;   // remember to free(list);
  else
    return 0;
}

int ifwinactive(char *rgxname)
{
  Window cid = wingettitle(); 
  Window wid = wingetid(rgxname);
  if (cid == wid)
    return 1;
  else
    return 0; 
}





int send(char *message, char *rgxname) {
  //  printf("in xsend");
  Window window = wingetid(rgxname);

int ret = 0;
  //  int i;
  //  int c;
  //  char *cmd ;
  //  charcodemap_t *keymods;
  // int nkeymods;

  /* Options */
  //  int clear_modifiers = 0;
  //  Window window = 0;
  useconds_t delay = 12000; /* 12ms between keystrokes default */


  /*  if (clear_modifiers) {
    xdo_active_modifiers_to_keycode_list(xdo, &keymods, &nkeymods);
    xdo_keysequence_list_do(xdo, window, keymods, nkeymods, False, NULL);
  }
  */


    ret = xdo_type(xdo, window, message, delay);
    // printf("typing %s", message);
    if (ret) {
      fprintf(stderr, "xdo_type reported an error\n");
    }

    /*
      if (clear_modifiers) {
      
      xdo_keysequence_list_do(xdo, window, keymods, nkeymods, True, NULL);
      free(keymods);
      }
    */
    return ret;
}



  /*
  struct option longopts[] = {
    { "window", required_argument, NULL, 'w' },
    { "delay", required_argument, NULL, 'd' },
    { "clearmodifiers", no_argument, NULL, 'c' },
    { 0, 0, 0, 0 },
  };
  */

  //for (i = 0; i < argc; i++) { printf("'%s' ", args[i]); }; printf("\n");
  /*  while (1) {
    int option_index;
    c = getopt_long(argc, args, "w:d:c", longopts, &option_index);

    switch (c) {
      case 'w':
        window = strtoul(optarg, NULL, 0);
        break;
      case 'd':
        --delay is in milliseconds, convert to microseconds 
        delay = strtoul(optarg, NULL, 0) * 1000;
        break;
      case 'c':
        clear_modifiers = 1;
        break;
    }

    if (c == -1) {
      break;
    }
  }
  */

  /*
  args += optind;
  argc -= optind;

  if (argc == 0) {
    fprintf(stderr, "You specified the wrong number of args.\n");
    fprintf(stderr, 
            "usage: %s [--window windowid] [--delay milliseconds] "
            "<things to type>\n"
            "--window <windowid>    - specify a window to send keys to\n"
            "--delay <milliseconds> - delay between keystrokes\n"
            "--clearmodifiers       - reset active modifiers (alt, etc) while typing\n"
            , cmd);
    return 1;
  }
  */
