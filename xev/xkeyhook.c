// todo: create xkeyhook.h 

/*  taken with permission under GPL v2 from 
 *  http://stllinux.org/meeting_notes/1997/0619/xkey.html
 *  by Dominic Giampaolo (nick@cs.maxine.wpi.edu)
 */

#include "xheaders.h"

char *TranslateKeyCode(XEvent *ev);


Display *d;

void snoop_all_windows(Window root, unsigned long type)
{
  static int level = 0;
  Window parent, *children, *child2;
  unsigned int nchildren;
  int stat, i,j,k;

  level++;

  stat = XQueryTree(d, root, &root, &parent, &children, &nchildren);
  if (stat == FALSE)
   {
     fprintf(stderr, "Can't query window tree...\n");
     return;
   }

  if (nchildren == 0)
    return;

  XSelectInput(d, root, type);

  for(i=0; i < nchildren; i++)
   {
     XSelectInput(d, children[i], type);
     snoop_all_windows(children[i], type);
   }

  XFree((char *)children);
}



#define KEY_BUFF_SIZE 256
static char key_buff[KEY_BUFF_SIZE];

char *TranslateKeyCode(XEvent *ev)
{
  int count;
  char *tmp;
  KeySym ks;

  if (ev)
   {
     count = XLookupString((XKeyEvent *)ev, key_buff, KEY_BUFF_SIZE, &ks,NULL);
     key_buff[count] = '\0';

     if (count == 0)
      {
        tmp = XKeysymToString(ks);
        if (tmp)
          strcpy(key_buff, tmp);
        else
          strcpy(key_buff, "");
      }

     return key_buff;
   }
  else
    return NULL;
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

  char buf[2] = {0};  // used to send key to ahk
  while(1)
   {
     XNextEvent(d, &xev);

     string = TranslateKeyCode(&xev);
     if (string == NULL)
       continue;
     else if (strlen(string) == 1)
       {
       printf("%s", string);
       buf[0] = *string;
       ahkKey(buf);        //       ahkLabel(buf);
       }
     else
       {       
	 printf("<<%s>>", string);
	 ahkKey(string);
       }
     fflush(stdout);
   }
}
