.386
.model flat,stdcall
option casemap:none
include		windows.inc
include		user32.inc
includelib	user32.lib
include		kernel32.inc
includelib	kernel32.lib
;include		comdlg32.inc
;includelib	comdlg32.lib
			.data
Buf			db 	100h dup(0)
			.const
FileName	db '1.exe',0
Box			db	'It',39,'s not a DOS program!',0
GetPeFile	db	'It',39,'s a DOS program',0
PeFile		db	'PE File',0
			.code
_WinMain	proc
	local	@hFile
	local	@dwFileSize
	local	@hMapFile
	local	@lpMemory
			invoke CreateFileA,addr FileName,\
				GENERIC_READ,FILE_SHARE_READ,NULL,\
					OPEN_ALWAYS,FILE_ATTRIBUTE_ARCHIVE,NULL
			.if eax!=INVALID_HANDLE_VALUE
				mov @hFile,eax
				invoke	GetFileSize,eax,NULL
				mov	@dwFileSize,eax
				.if eax
					invoke CreateFileMapping,@hFile,NULL,PAGE_READONLY,0,0,NULL
					.if eax
						mov @hMapFile,eax
						invoke	MapViewOfFile,eax,FILE_MAP_READ,0,0,0
						.if	eax
							mov @lpMemory,eax
						.endif
					.endif
				.endif
			.endif
			mov esi,@lpMemory
			push esi
			assume	esi:ptr	IMAGE_DOS_HEADER
			.if	[esi].e_magic != IMAGE_DOS_SIGNATURE
				invoke MessageBoxA,0,addr Box,addr PeFile,0
				ret
			.endif
			invoke MessageBoxA,0,addr GetPeFile,addr PeFile,0
;>>>>>>>>>>>IMAGE_DOS_HEADER MZ
			xor eax,eax
			mov ax,[esi].e_magic
			mov dword ptr Buf,eax
			invoke MessageBoxA,0,addr Buf,addr PeFile,0
;>>>>>>>>>>>IMAGE_DOS_HEADER MZ
;>>>>>>>>>>>IMAGE_NT_HEADER PE00
			add esi,[esi].e_lfanew
			mov eax,dword ptr [esi]
			mov dword ptr Buf,eax
			invoke MessageBoxA,0,addr Buf,addr PeFile,0
;>>>>>>>>>>>IMAGE_NT_HEADER PE00
;>>>>>>>>>>>IMAGE_NT_HEADER PE00
			pop esi
			add esi,dword ptr [esi+03ch]
			mov eax,dword ptr [esi]
			mov dword ptr Buf,eax
			invoke MessageBoxA,0,addr Buf,addr PeFile,0
;>>>>>>>>>>>IMAGE_NT_HEADER PE00
			ret
_WinMain 	endp
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
start:
	call	_WinMain
	invoke	ExitProcess,NULL
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.
	end start