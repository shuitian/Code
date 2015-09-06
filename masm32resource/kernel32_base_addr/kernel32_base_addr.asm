.386
.model flat,stdcall
option casemap:none
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; include 文件定义
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
include		windows.inc
include		user32.inc
includelib	user32.lib
include		kernel32.inc
includelib	kernel32.lib
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			.code
;>>>>>>>>>>>>>>>>>>>>>>>
kernel32base	dd	?
Error			db	"Error",0
GetKerBasAddErr	db	"GetKerBasAddErr!",0
Succ			db	"Success",0
GetKerBasAddSuc db	"GetKerBasAddSuc!",0
_GetKerBaAddr		proc
	mov eax,[esp+4]
	pushad
	and eax,0ffff0000h
	.repeat
		.if word ptr[eax]==IMAGE_DOS_SIGNATURE
			mov edx,[eax+3ch]
			add edx,eax
			.if dword ptr[edx]==IMAGE_NT_SIGNATURE
				mov kernel32base,eax
				popad
				ret
			.endif
		.endif
		sub eax,010000h
	.until	eax<070000000h
	.if eax<070000000h
		xor eax,eax
	.endif
	popad
	ret
_GetKerBaAddr 	endp
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
start:
	call	_GetKerBaAddr
	call @1
@1:	pop ebx
	sub ebx,@1
	.if eax==0
		push 0
		lea eax,Error
		add eax,ebx
		push eax
		lea eax,GetKerBasAddErr
		add eax,ebx
		push eax
		push 0
		call MessageBoxA
		jmp @f
	.endif
	push 0
	lea eax,Succ
	add eax,ebx
	push eax
	lea eax,GetKerBasAddSuc
	add eax,ebx
	push eax
	push 0
	call MessageBoxA
	invoke MessageBoxA,NULL,addr GetKerBasAddSuc,addr Succ,MB_OK
	mov eax,kernel32base
	add 	eax,0005BBE2h
	call 	eax
@@:	invoke ExitProcess,NULL
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.
	end start