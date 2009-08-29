/*
AutoHotkey

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

#include "stdafx.h" // pre-compiled headers
#include "script.h"
#include "globaldata.h" // for a lot of things
#include "util.h" // for strlcpy() etc.
// #include "mt19937ar-cok.h" // for random number generator
#include "window.h" // for a lot of things
#include "application.h" // for MsgSleep()
// #include "exports.h" // Naveen v8
// Globals that are for only this module:

#ifndef ZeroMemory
#include <memory.h>
#define ZeroMemory(PTR, SIZE) memset(PTR, 0, SIZE)
#endif // ZeroMemory


#define MAX_COMMENT_FLAG_LENGTH 15
static char g_CommentFlag[MAX_COMMENT_FLAG_LENGTH + 1] = ";"; // Adjust the below for any changes.
static size_t g_CommentFlagLength = 1; // pre-calculated for performance

// General note about the methods in here:
// Want to be able to support multiple simultaneous points of execution
// because more than one subroutine can be executing simultaneously
// (well, more precisely, there can be more than one script subroutine
// that's in a "currently running" state, even though all such subroutines,
// except for the most recent one, are suspended.  So keep this in mind when
// using things such as static data members or static local variables.


Script::Script()
	: mFirstLine(NULL), mLastLine(NULL), mCurrLine(NULL), mPlaceholderLabel(NULL), mLineCount(0)
	, mThisHotkeyName(""), mPriorHotkeyName(""), mThisHotkeyStartTime(0), mPriorHotkeyStartTime(0)
	, mEndChar(0), mThisHotkeyModifiersLR(0)
	, mNextClipboardViewer(NULL), mOnClipboardChangeIsRunning(false), mOnClipboardChangeLabel(NULL)
	, mOnExitLabel(NULL), mExitReason(EXIT_NONE)
	, mFirstLabel(NULL), mLastLabel(NULL)
	, /*mFirstFunc(NULL),*/ mLastFunc(NULL), mFunc(NULL), mFuncCount(0), mFuncCountMax(0) // L27: Removed mFirstFunc, added mFunc, mFuncCount, mFuncCountMax.
	, mFirstTimer(NULL), mLastTimer(NULL), mTimerEnabledCount(0), mTimerCount(0)
	, mFirstMenu(NULL), mLastMenu(NULL), mMenuCount(0)
	, mVar(NULL), mVarCount(0), mVarCountMax(0), mLazyVar(NULL), mLazyVarCount(0)
	, mCurrentFuncOpenBlockCount(0), mNextLineIsFunctionBody(false)
	, mFuncExceptionVar(NULL), mFuncExceptionVarCount(0)
	, mCurrFileIndex(0), mCombinedLineNumber(0), mNoHotkeyLabels(true), mMenuUseErrorLevel(false)
	, mFileSpec(""), mFileDir(""), mFileName(""), mOurEXE(""), mOurEXEDir(""), mMainWindowTitle("")
	, mIsReadyToExecute(false), mAutoExecSectionIsRunning(false)
	, mIsRestart(false), mIsAutoIt2(false), mErrorStdOut(false)
#ifdef AUTOHOTKEYSC
	, mCompiledHasCustomIcon(false)
#else
	, mIncludeLibraryFunctionsThenExit(NULL)
#endif
	, mLinesExecutedThisCycle(0), mUninterruptedLineCountMax(1000), mUninterruptibleTime(15)
	, mRunAsUser(NULL), mRunAsPass(NULL), mRunAsDomain(NULL)
	, mCustomIcon(NULL), mCustomIconSmall(NULL) // Normally NULL unless there's a custom tray icon loaded dynamically.
	, mCustomIconFile(NULL), mIconFrozen(false), mTrayIconTip(NULL) // Allocated on first use.
	, mCustomIconNumber(0)
{
	// v1.0.25: mLastScriptRest and mLastPeekTime are now initialized right before the auto-exec
	// section of the script is launched, which avoids an initial Sleep(10) in ExecUntil
	// that would otherwise occur.
	*mThisMenuItemName = *mThisMenuName = '\0';
	ZeroMemory(&mNIC, sizeof(mNIC));  // Constructor initializes this, to be safe.
	mNIC.hWnd = NULL;  // Set this as an indicator that it tray icon is not installed.

	// Lastly (after the above have been initialized), anything that can fail:
	if (   !(mTrayMenu = AddMenu("Tray"))   ) // realistically never happens
	{
		ScriptError("No tray mem");
		ExitApp(EXIT_CRITICAL);
	}
	else
		mTrayMenu->mIncludeStandardItems = true;

#ifdef _DEBUG
	if (ID_FILE_EXIT < ID_MAIN_FIRST) // Not a very thorough check.
		ScriptError("DEBUG: ID_FILE_EXIT is too large (conflicts with IDs reserved via ID_USER_FIRST).");
	if (MAX_CONTROLS_PER_GUI > ID_USER_FIRST - 3)
		ScriptError("DEBUG: MAX_CONTROLS_PER_GUI is too large (conflicts with IDs reserved via ID_USER_FIRST).");
	int LargestMaxParams, i, j;
	ActionTypeType *np;
	// Find the Largest value of MaxParams used by any command and make sure it
	// isn't something larger than expected by the parsing routines:
	for (LargestMaxParams = i = 0; i < g_ActionCount; ++i)
	{
		if (g_act[i].MaxParams > LargestMaxParams)
			LargestMaxParams = g_act[i].MaxParams;
		// This next part has been tested and it does work, but only if one of the arrays
		// contains exactly MAX_NUMERIC_PARAMS number of elements and isn't zero terminated.
		// Relies on short-circuit boolean order:
		for (np = g_act[i].NumericParams, j = 0; j < MAX_NUMERIC_PARAMS && *np; ++j, ++np);
		if (j >= MAX_NUMERIC_PARAMS)
		{
			ScriptError("DEBUG: At least one command has a NumericParams array that isn't zero-terminated."
				"  This would result in reading beyond the bounds of the array.");
			return;
		}
	}
	if (LargestMaxParams > MAX_ARGS)
		ScriptError("DEBUG: At least one command supports more arguments than allowed.");
	if (sizeof(ActionTypeType) == 1 && g_ActionCount > 256)
		ScriptError("DEBUG: Since there are now more than 256 Action Types, the ActionTypeType"
			" typedef must be changed.");
#endif
}


