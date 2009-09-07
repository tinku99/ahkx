// sudo python evdev.py /dev/input/by-path/*-event-kbd | sh pipe
// winegcc -o pipe.exe pipe.c
// cat pipe.c | sh pipe

#include <stdio.h>
#include <string.h>

int main()
{
  char word[2] = {0};
  while (scanf("%1s", word) == 1)
    printf ("%s\n", word);
  return 0;
}
