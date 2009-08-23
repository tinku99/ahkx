#include "ctype.h"
#include "stdio.h"
// #include "stdafx.h" // pre-compiled headers
// #include "defines.h"

// #define ltolower(ch) CharLower((LPSTR)(UCHAR)(ch))
// #define ltolower(ch) CharLower((LPTSTR)(0x00ff & ch))
// #define ltolower(ch) CharLower(0x00ff & ch)

#define ltolower(ch) tolower(ch)  
#define ltoupper(ch) toupper((int)(UCHAR)(ch))  


int main(){
      char aStr[10] = "HELLO\0";
    //     *aStr = (char)ltolower(aStr);
       aStr[0] = (char)ltolower(*aStr);
    printf("%s", aStr); 
    printf("%d", true);
    return 0;
}
