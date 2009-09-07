F1::
; DllCall(A_ScriptDir . "\AutoHotkey.exe\ahkKey", "uchar", 65, "cdecl")
msgbox  % errorlevel
return
a::
msgbox a
return

/*a
a
wparam: 256
vkcode: 65
scancode 30
flags 0
time: 
dwxtrainfo 0
keyup true
vk 0xcc

b
100
42
30
0
timea
0
true
oxcc
*/
