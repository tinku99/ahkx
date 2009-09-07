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
#include <string.h>
#include "wineheaders.h"  // must come before xheaders 
#include "xheaders.h"
#include "xkeyhook.c"

int (*ahkdll)(char *, char *, char *) ;
unsigned int (*ahkLabel)(char *) ;
unsigned int (*ahkKey)(char *) ;
unsigned int (*ahkCollect)(char *) ;

int main(int argc, char **argv)
{
  //  extern ahkLabel, ahkdll;
  void * dll_handle = WineLoadLibrary("AutoHotkey.dll" );
  char *script; 
  if (argv[1] == NULL)
    script = "simplehook.ahk";
  else
    script = argv[1];

    ahkdll = WineGetProcAddress( dll_handle, "ahkdll" );
    ahkLabel = WineGetProcAddress( dll_handle, "ahkLabel" );
    ahkKey = WineGetProcAddress( dll_handle, "ahkKey" );
    ahkCollect = WineGetProcAddress( dll_handle, "ahkCollect" );

    ahkdll(script, "", "");
    sleep(2);
    //    ahkLabel("k");
    char *key = "k";  // not used right now
    xkey(ahkLabel, key);
    return 0 ;
}


int xkey(unsigned int (*ahkLabel)(char *), char *key)
{
  char *hostname;
  char *string;
  XEvent xev;
  int count = 0;
  hostname = ":0";
  /* 
    hostname = argv[1];
  */


  d = XOpenDisplay(hostname);
  if (d == NULL)
   {
     fprintf(stderr, "Blah, can't open display: %s\n", hostname);
     return 10;
   }

  snoop_all_windows(DefaultRootWindow(d), KeyPressMask);

  char buf[2] = {0};  // used to send key to ahk
  while(1)
   {
     XNextEvent(d, &xev);

     string = TranslateKeyCode(&xev);
     if (string == NULL)
       continue;
     else if (*string == 'a')
       {
	 printf("eventa%d\n", ahkKey("a"));
       }
     else if (*string == 'b')
       {
	 printf("events%d\n", ahkKey("s"));
	 printf("eventd%d\n", ahkKey("d"));
	 printf("eventd%d\n", ahkKey(" "));
	 printf("eventd%d\n", ahkKey(" "));
       }
     else if (*string == '\r')
       printf("\n");
     else if (strlen(string) == 1)
       {
       printf("%s", string);
       buf[0] = *string;
       ahkLabel(buf);
       }
     else
       printf("<<%s>>", string);
     fflush(stdout);
   }
}

