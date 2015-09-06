.386
.model flat,stdcall
option casemap:none
include		windows.inc
include		user32.inc
includelib	user32.lib
include		kernel32.inc
includelib	kernel32.lib
	.data
mem dd ?
			.code
;>>>>>>>>>>>>>>>>>>>>>>>

start:
			db 100 dup(90h)
			nop
			
			inc eax
			jmp start
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.
	end start