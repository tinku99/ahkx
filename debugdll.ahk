start:
ahkdll := DllCall("LoadLibrary", "str", A_ScriptDir . "\AutoHotkey.dll")
threadH := DllCall(A_ScriptDir . "\AutoHotkey.dll\ahkdll", "str", "hotkey.ahk", "Cdecl Int")

F1::
DllCall(A_ScriptDir . "\AutoHotkey.dll\ahkKey", "str", "a", "cdecl")
msgbox  % errorlevel
return

F2::
DllCall(A_ScriptDir . "\AutoHotkey.dll\ahkKey", "str", "b", "cdecl")
DllCall(A_ScriptDir . "\AutoHotkey.dll\ahkKey", "str", "a", "cdecl")
return

F3::
DllCall(A_ScriptDir . "\AutoHotkey.dll\ahkCollect", "str", "b", "cdecl")
DllCall(A_ScriptDir . "\AutoHotkey.dll\ahkCollect", "str", "a", "cdecl")
return
return
!q::ExitApp
!r::Reload
