#ifndef linuxtypes_h
#define linuxtypes_h

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
// #define _itoa itoa 
extern "C" {
#define UINT_PTR unsigned int
#define LONG_PTR long
#define ULONG_PTR unsigned long
#define DWORD_PTR unsigned long
#define _strtoi64 strtoll
#define _strtoui64 strtoull 
#define IsCharAlpha isalpha
#define MAKEPOINTS(l) (*((POINTS*)&(l)))
#define MAKEROP4(f,b)	(DWORD)((((b)<<8)&0xFF000000)|(f))
#define GetCValue(cmyk) ((BYTE)(cmyk))
#define GetMValue(cmyk) ((BYTE)((cmyk)>> 8))
#define GetYValue(cmyk) ((BYTE)((cmyk)>>16))
#define GetKValue(cmyk) ((BYTE)((cmyk)>>24))
#define CMYK(c,m,y,k) ((COLORREF)((BYTE)(k)|((BYTE)(y)<<8)|((BYTE)(m)<<16)|((BYTE)(c)<<24)))
#define GetRValue(c) ((BYTE)(c))
#define GetGValue(c) ((BYTE)(((WORD)(c))>>8))
#define GetBValue(c) ((BYTE)((c)>>16))
#define RGB(r,g,b) ((COLORREF)((BYTE)(r)|((BYTE)(g) << 8)|((BYTE)(b) << 16)))
#define PALETTEINDEX(i)	((0x01000000|(COLORREF)(WORD)(i)))
#define PALETTERGB(r,g,b)	(0x02000000|RGB(r,g,b))
#define LF_FACESIZE	32
#define LF_FULLFACESIZE	64

#define MAX_PATH 260
#define CF_TEXT	1
#define CF_BITMAP	2
#define CF_METAFILEPICT	3
#define CF_SYLK	4
#define CF_DIF	5
#define CF_TIFF	6
#define CF_OEMTEXT	7
#define CF_DIB	8
#define CF_PALETTE	9
#define CF_PENDATA	10
#define CF_RIFF	11
#define CF_WAVE	12
#define CF_UNICODETEXT	13
#define CF_ENHMETAFILE	14
#define CF_HDROP	15
#define CF_LOCALE	16
#define CF_MAX	17
#define CF_OWNERDISPLAY	128
#define CF_DSPTEXT	129
#define CF_DSPBITMAP	130
#define CF_DSPMETAFILEPICT	131
#define CF_DSPENHMETAFILE	142
#define CF_PRIVATEFIRST	512
#define CF_PRIVATELAST	767
#define CF_GDIOBJFIRST	768
#define CF_GDIOBJLAST	1023
} // extern c close



typedef char BYTE; 
typedef unsigned short      WORD;
typedef char     TCHAR; 
typedef time_t SYSTEMTIME;
typedef int64_t __int64 ;
typedef long LONG;
typedef unsigned char UCHAR ;
typedef unsigned int UINT; 
typedef UINT DWORD;
typedef void * HANDLE;
typedef void * LPVOID;
typedef void * PVOID;
typedef bool BOOL;
typedef DWORD *LPCOLORREF;
typedef TCHAR *LPTSTR;
typedef const TCHAR *LPCTSTR;



typedef HANDLE HWND ;
typedef HANDLE LPCWSTR;
typedef HANDLE HKEY;
typedef HANDLE HGLOBAL;
typedef HANDLE HBRUSH; 
typedef HANDLE HRESULT;
typedef HANDLE HDC;
typedef HANDLE HBITMAP;
typedef HANDLE HMODULE;
typedef HANDLE HICON;

typedef struct {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
}FILETIME, *PFILETIME;
// todo: use struct stat instead from #include <sys/stat.h>

typedef struct {
  DWORD    dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD    nFileSizeHigh;
  DWORD    nFileSizeLow;
  DWORD    dwReserved0;
  DWORD    dwReserved1;
  TCHAR    cFileName[MAX_PATH];
  TCHAR    cAlternateFileName[14];
}WIN32_FIND_DATA, *PWIN32_FIND_DATA, *LPWIN32_FIND_DATA;

typedef struct {
  LONG x;
  LONG y;
} POINT;
typedef DWORD COLORREF;
typedef struct { 
  LONG lfHeight; 
  LONG lfWidth; 
  LONG lfEscapement; 
  LONG lfOrientation; 
  LONG lfWeight; 
  BYTE lfItalic; 
  BYTE lfUnderline; 
  BYTE lfStrikeOut; 
  BYTE lfCharSet; 
  BYTE lfOutPrecision; 
  BYTE lfClipPrecision; 
  BYTE lfQuality; 
  BYTE lfPitchAndFamily; 
  TCHAR lfFaceName[LF_FACESIZE]; 
} LOGFONT; 
typedef struct {
  LOGFONT elfLogFont;
  TCHAR   elfFullName[LF_FULLFACESIZE];
  TCHAR   elfStyle[LF_FACESIZE];
  TCHAR   elfScript[LF_FACESIZE];
}ENUMLOGFONTEX;





#endif // #ifndef linuxtypes_h