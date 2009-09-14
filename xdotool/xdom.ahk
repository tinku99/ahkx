#InstallKeybdHook
#UseHook
#Persistent
ahkdll := DllCall("LoadLibrary", "str", A_ScriptDir . "\xdotool.dll.so")
DllCall(A_ScriptDir . "\xdotool.dll.so\xinit", "cdecl") 
return

q::exitapp

n::
ifwinactive, naveen
msgbox naveen active
else
msgbox naveen not active
return


return
i:: 
DllCall(A_ScriptDir . "\xdotool.dll.so\xmousemove"
, "int", 0, "int", -20, "int", 1, "cdecl") 
return


k:: 
DllCall(A_ScriptDir . "\xdotool.dll.so\xmousemove"
, "int", 0, "int", 20, "int", 1, "cdecl") 
return


j:: 
DllCall(A_ScriptDir . "\xdotool.dll.so\xmousemove"
, "int", -20, "int", 0, "int", 1, "cdecl") 
return


l:: 
DllCall(A_ScriptDir . "\xdotool.dll.so\xmousemove"
, "int", 20, "int", 0, "int", 1, "cdecl") 
return

p::
coordmode, mouse, screen
mousegetpos, xa, ya
DllCall(A_ScriptDir . "\xdotool.dll.so\xmousegetpos"
, "int *", x, "int *", y, "int *", screen, "cdecl") 
msgbox % "mouse pos from x11 `n" . x . "`n" . y . "`n" . screen

msgbox % "mouse pos from ahk" .  xa . "`n" . ya . "`n" . title
return

c::
DllCall(A_ScriptDir . "\xdotool.dll.so\xmousegetpos"
, "int *", x, "int *", y, "int *", screen, "cdecl") 
inputbox, button, button
DllCall(A_ScriptDir . "\xdotool.dll.so\xmouseclick"
, "int", x, "int", y, "int", button, "int", 0, "cdecl") 
DllCall(A_ScriptDir . "\xdotool.dll.so\xmouseclick"
, "int", x, "int", y, "int", button, "int", 1, "cdecl") 
return


y::
suspend, on
inputbox, title, title
suspend, off
return

t:: 
if !title
inputbox, title, title
WinGetTitle, ahktitle, % title
xdoid := DllCall(A_ScriptDir . "\xdotool.dll.so\xwingetid"
, "str", title, "cdecl UInt") 
current := DllCall(A_ScriptDir . "\xdotool.dll.so\xwingettitle"
, "cdecl UInt") 
msgbox % xdoid . "`n" . current . "`n" . ahktitle
return

a:: 
DllCall(A_ScriptDir . "\xdotool.dll.so\xwinactivate"
, "str", "xdo", "cdecl UInt") 
return


r:: 
DllCall(A_ScriptDir . "\xdotool.dll.so\xwinrestore"
, "str", "xdo", "cdecl UInt") 
return


m:: 
DllCall(A_ScriptDir . "\xdotool.dll.so\xwinmove"
, "str", "xdo", "int", 100, "int", 100, "cdecl UInt") 
return
