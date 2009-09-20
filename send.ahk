#InstallKeybdHook
#UseHook 
; SendMode Input

#IfWinActive ^naveen
a::
msgbox test
return

#IfWinActive 

F4::
sendevent, a
return


F5::
send, a
return

F6::
sendplay, a
return



