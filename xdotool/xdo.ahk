#InstallKeybdHook
#UseHook
#Persistent
ahkdll := DllCall("LoadLibrary", "str", A_ScriptDir . "\xdotool.dll.so")
sleep, 500
DllCall(A_ScriptDir . "\xdotool.dll.so\xinit", "cdecl") 

DllCall(A_ScriptDir . "\xdotool.dll.so\xmousemove"
, "int", 200, "int", 200, "int", 0, "cdecl") 
msgbox % moved to 200 200
DllCall(A_ScriptDir . "\xdotool.dll.so\xmousemove"
, "int", 200, "int", 200, "char", 1, "cdecl") 
msgbox % ErrorLevel

return

q::exitapp
