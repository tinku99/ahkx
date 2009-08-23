#ifndef linuxtypes2_h
#define linuxtypes2_h
// const_cast<char*> for returning a modifiable string instead of const char
#include "stdafx.h"
#include "defines.h"
#include <ctype.h>

extern "C" {
#define __forceinline
#define LLMHF_INJECTED 0x00000001
#define IDCONTINUE 11
#define IDTRYAGAIN 10
#define MIXERCONTROL_CONTROLTYPE_BASS_BOOST     (MIXERCONTROL_CONTROLTYPE_BOOLEAN + 0x00002277)
#define LPLVITEM LPLVITEMW
#define CF_DIBV5 17
#define TreeView_GetCheckState(hwndTV, hti) \
   ((((UINT)(SendMessageA((hwndTV), TVM_GETITEMSTATE, (WPARAM)(hti),  \
                     TVIS_STATEIMAGEMASK))) >> 12) -1)
#define SBARS_TOOLTIPS 0x0800
#define BS_TYPEMASK 0x0000000FL
#define LV_VIEW_TILE 0x0004
#define LVN_HOTTRACK (LVN_FIRST-21)
#define LVN_BEGINSCROLL (LVN_FIRST-80)
#define LVN_ENDSCROLL (LVN_FIRST-81)
#define LVN_MARQUEEBEGIN (LVN_FIRST-56)
#define MIM_BACKGROUND 2
#define MIM_APPLYTOSUBMENUS 0x80000000L

  // from mingw winnt.h
#define MINCHAR	0x80
#define MAXCHAR	0x7f
#define MINSHORT	0x8000
#define MAXSHORT	0x7fff
#define MINLONG	0x80000000
#define MAXLONG	0x7fffffff
#define MAXBYTE	0xff
#define MAXWORD	0xffff
#define MAXDWORD	0xffffffff
#define TRUE true

} // extern c close


typedef struct {
    HWND hwndFrom;
    UINT_PTR idFrom;
    UINT code;
} NMHDR;

typedef struct {
    NMHDR hdr;
    WORD wVKey;
    UINT flags;
} NMTVKEYDOWN, *LPNMTVKEYDOWN;




#endif  //  #ifndef linuxtypes2_h
