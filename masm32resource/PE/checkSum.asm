.386
.model flat,stdcall
option casemap:none
include		windows.inc
include		user32.inc
includelib	user32.lib
include		kernel32.inc
includelib	kernel32.lib
include		imagehlp.inc
includelib	imagehlp.lib
;include		comdlg32.inc
;includelib	comdlg32.lib
			.data
Buf			db 	100h dup(0)
			.const
FileName	db 'c:\windows\system32\kernel32.dll',0
Box			db	'It',39,'s not a DOS program!',0
GetPeFile	db	'It',39,'s a DOS program',0
PeFile		db	'PE File',0
			.code
_WinMain	proc
	local	@hFile
	local	@dwFileSize
	local	@hMapFile
	local	@lpMemory
	local 	@cSum,@hSum
	local	@ret
	
	pushad
	invoke MapFileAndCheckSum,addr FileName,\
			addr @hSum,addr @cSum
	mov eax,@cSum
	mov @ret,eax
	popad
	mov eax,@ret
	ret
_WinMain	endp

_WinMain1	proc
	local	hFile,dwSize,hBase
	local	@size
	local	@ret
	
	pushad
	invoke CreateFile,addr FileName,\
			GENERIC_READ,FILE_SHARE_READ,\
				NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0
	mov 	hFile,eax
	invoke 	GetFileSize,hFile,NULL
	mov 	dwSize,eax
	invoke	VirtualAlloc,NULL,dwSize,\
				MEM_COMMIT,PAGE_READWRITE
	mov 	hBase,eax
	invoke	ReadFile,hFile,hBase,dwSize,addr @size,NULL
	invoke	CloseHandle,hFile
	
	;clear CheckSum
	mov 	ebx,hBase
	assume	ebx:ptr IMAGE_DOS_HEADER
	mov 	ebx,[ebx].e_lfanew
	add		ebx,hBase
	assume	ebx:ptr	IMAGE_NT_HEADERS
	mov		[ebx].OptionalHeader.CheckSum,0
	assume	ebx:ptr nothing
	
	mov 	ecx,dwSize
	inc 	ecx
	shr		ecx,1
	mov 	esi,hBase
	xor		ebx,ebx
	clc
lop:
	lodsw
	adc		bx,ax
	loop	lop
	
	invoke	VirtualFree,hBase,dwSize,MEM_DECOMMIT
	
	add		ebx,dwSize
	mov 	@ret,ebx
	
	popad
	mov 	eax,@ret
	ret
_WinMain1	endp
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
start:
	call	_WinMain1
	invoke	ExitProcess,NULL
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.
	end start