// gcc -I/home/naveen/source/include -o stdafx.o stdafx.h
// g++ -o stdafx.o stdafx.h
// include mingw headers above
/*
AutoHotkey GCC 

Copyright 2009 Naveen Garg (naveen.garg@gmail.com)
Copyright 2003-2009 Chris Mallett (support@autohotkey.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once  

	// C RunTime Header Files
        #include <ctype.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdarg.h> // used by snprintfcat()
	#include <limits.h> // for UINT_MAX, UCHAR_MAX, etc.
	#include <malloc.h> // For _alloca()

#include "linuxtypes.h"
#include "linuxtypes2.h"

        
//        #include "mingw/winbase.h"
	//#include <memory.h>
	//#include <tchar.h>

//	#include "windows.h"
// todo: linux versions of <commctrl.h> <shellapi.h> <shlobj.h>  /<mmsystem.h> <commdlg.h> 

//	#include <commctrl.h> // for status bar functions. Must be included after <windows.h>.
//	#include <shellapi.h>  // for ShellExecute()
//	#include <shlobj.h>  // for SHGetMalloc()
//	#include <mmsystem.h> // for mciSendString() and waveOutSetVolume()
//	#include <commdlg.h> // for OPENFILENAME

	// It's probably best not to do these, because I think they would then be included
	// for everything, even modules that don't need it, which might result in undesired
	// dependencies sneaking in, or subtle naming conflicts:
	// ...
	//#include "defines.h"
	//#include "application.h"
	//#include "globaldata.h"
	//#include "window.h"  // Not to be confused with "windows.h"
	//#include "util.h"
	//#include "SimpleHeap.h"


// Lexikos: Defining _WIN32_WINNT 0x0600 seems to break TrayTip in non-English Windows, and possibly other things.
//			Instead, define only the necessary constants for horizontal wheel support in Windows Vista and later.
// todo: linux constants
#if (_WIN32_WINNT < 0x0600)
#define WM_MOUSEHWHEEL      0x020E
#define MOUSEEVENTF_HWHEEL  0x01000 /* hwheel button rolled */
#endif
