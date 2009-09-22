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
typedef int (* ahkx_int_str)(char *ahkx_str); // ahkx N11
typedef int (* ahkx_int_str_str)(char *ahkx_str, char *ahkx_str2); // ahkx N11

int (*ahkdll)(char *, char *, char *) ;
unsigned int (*ahkLabel)(char *) ;
// unsigned int (*ahkFunction)(char *, char *, char *, char *, char *) ;
unsigned int (*ahkKey)(char *) ;
// unsigned int (*ahkCollect)(char *) ;
unsigned int (*ximportfunc)(int (*)(char *), int (*)(char *)
			    ,int (*)(char *, char *)) ;
ahkx_int_str xifwinactive;  // int (* xifwinactive)(char *ahkx_str);
ahkx_int_str xwingetid;
ahkx_int_str_str xsend;
void (* xinit)(void);
int main(int argc, char **argv)
{
  //  extern ahkLabel, ahkdll;
  //  void * dll_handle = WineLoadLibrary("AutoHotkey.dll" );
  void * dll_handle = WineLoadLibrary("ahkx.so" ); // ahkx.dll
    printf("%d%s", (int)dll_handle, "ahkxhandle");
  void * xdo_handle = WineLoadLibrary("xdotool.dll.so" ); // ahkx.dll
  char *script; 
  if (argv[1] == NULL)
    script = "simplehook.ahk";
  else
    script = argv[1];

    ahkdll = WineGetProcAddress( dll_handle, "ahkdll" );
    ahkLabel = WineGetProcAddress( dll_handle, "ahkLabel" );
    // ahkFunction = WineGetProcAddress( dll_handle, "ahkFunction" );
    ahkKey = WineGetProcAddress( dll_handle, "ahkKey" );
    // ahkCollect = WineGetProcAddress( dll_handle, "ahkCollect" );
    ximportfunc = WineGetProcAddress( dll_handle, "ximportfunc" );
    xifwinactive = WineGetProcAddress( xdo_handle, "xifwinactive" );
    xwingetid = WineGetProcAddress( xdo_handle, "xwingetid" );
    xsend = WineGetProcAddress( xdo_handle, "xsend" );
    xinit = WineGetProcAddress( xdo_handle, "xinit" );
    printf("%d%s\n", (int)ahkdll, "ahkdll");
    printf("%d%s\n", (int)ximportfunc, "ximportfunc");
    printf("%d%s\n", (int)xifwinactive, "xifwinactive");
    printf("%d%s\n", (int)xwingetid, "xwingetid");
    printf("%d%s\n", (int)xsend, "xsend");
    printf("%d%s\n", (int)ahkLabel, "ahkLabel");
    //    printf("%d%s\n", (int)ahkFunction, "ahkFunction");
    printf("%d%s\n", (int)ahkKey, "ahkKey");
    
    //    xwingetid("naveen");
    //    xsend("from xsend", "naveen");

    ahkdll(script, "", "");
    sleep(2);
    xinit();
    int success = ximportfunc(xifwinactive, xwingetid, xsend);
    printf("%d%s\n", success, "transferred");
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

  d = XOpenDisplay(hostname);
  if (d == NULL)
   {
     fprintf(stderr, "Blah, can't open display: %s\n", hostname);
     return 10;
   }

  snoop_all_windows(DefaultRootWindow(d), KeyPressMask);

  char buf[20] = {0};  // used to send key to ahk
  while(1)
   {
     //     sleep(10);
     //     continue ; 
     XNextEvent(d, &xev);

     string = TranslateKeyCode(&xev);

    if (string == NULL)
       continue;
     else if (strlen(string) == 1)
       {
       printf("%s\n", string);
       buf[0] = *string;
       ahkKey(buf);        //       ahkLabel(buf);
       //	 ahkFunction("msgbox", buf, "", "", "");
       }
     else
       {       
	 printf("<<%s>>", string);
	 ahkLabel(string); 
       }
     fflush(stdout);
    
}
}

