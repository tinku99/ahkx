#InstallKeybdHook
#UseHook
#Persistent
ahkdll := DllCall("LoadLibrary", "str", A_ScriptDir . "\xdotool.dll.so")
sleep, 500
msgbox % DllCall(A_ScriptDir . "\xdotool.dll.so\xmousemove"
, "int", 200, "int", 200, "cdecl") 
msgbox % ErrorLevel
return

q::exitapp
