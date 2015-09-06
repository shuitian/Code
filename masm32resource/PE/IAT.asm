.386
.model flat,stdcall
option casemap:none
include		windows.inc
include		user32.inc
includelib	user32.lib
include		kernel32.inc
includelib	kernel32.lib

.data
sz1	db 'Shell_TrayWnd',0
hTray dd 0
			.code

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
start:
	invoke FindWindow,addr sz1,0
	mov hTray,eax
	invoke	ShowWindow,hTray,SW_SHOW
	invoke EnableWindow,hTray,TRUE
	invoke	MessageBoxA,0,NULL,NULL,0
	invoke	ExitProcess,NULL
	db 90h
	invoke ExitProcess,NULL
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.
	end start