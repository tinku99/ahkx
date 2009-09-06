// todo: create xkeyhook.h 

/*  taken from code in xkey.c by 
 *  Dominic Giampaolo (nick@cs.maxine.wpi.edu)
 *  http://stllinux.org/meeting_notes/1997/0619/xkey.html
 *  unknown license, although Dominic has released other things underl GPL
 *  such as libsx: http://freshmeat.net/projects/libsx/
 *  will likely replace this wih a device based keyboard hook soon anyway.
 */

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
