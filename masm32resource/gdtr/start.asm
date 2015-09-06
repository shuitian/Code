.386
.model flat,stdcall
option casemap:none
include		windows.inc
include		user32.inc
includelib	user32.lib
include		kernel32.inc
includelib	kernel32.lib
			.data?
GDT db 6 dup(?)
LDT dw ?
_cr0 db 10h dup(?)
			.code
_WinMain		proc
			sgdt GDT
			sldt LDT
			;push cr0
			cli
			mov eax,cr0
;and eax,0fffeffffh
mov cr0,eax
			
			sti
			ret
_WinMain 	endp
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
start:
	call	_WinMain
	invoke	ExitProcess,NULL
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.
	end start