#include "stdlib.h"
#include "stdio.h"

main()
{
  char *buf = "34\0" ; 
  printf("%d", atoll(buf));
}
