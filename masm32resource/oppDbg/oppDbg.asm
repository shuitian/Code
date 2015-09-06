.386
.model flat,stdcall
option casemap:none
include		windows.inc
include		user32.inc
includelib	user32.lib
include		kernel32.inc
includelib	kernel32.lib
			.data?
crc1	db	?
			.code
;>>>>>>>>>>>>>>>>>>>>>>>
_WinMain	proc
			xor eax,eax
			lea esi,start
begin:		lodsb
			add ah,al
			cmp esi,offset end1
			jb begin
			mov crc1,ah
			ret
_WinMain 	endp
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
start:
	call	_WinMain
	invoke ExitProcess,0
end1:
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.
	end start