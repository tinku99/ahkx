/*
winegcc -o ahkx.exe ahkx.c -ldl -lX11
or
sh build
sh run
*/


#include <stdio.h>
#include <string.h>
#include "wineheaders.h"  // must come before xheaders 
#include "xheaders.h"
#include "xkeyhook.c"

int (*ahkdll)(char *, char *, char *) ;
unsigned int (*ahkLabel)(char *) ;

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

     if (*string == '\r')
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

