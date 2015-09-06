.386
.model flat,stdcall
option casemap:none
include		windows.inc
include		user32.inc
includelib	user32.lib
include		kernel32.inc
includelib	kernel32.lib
include		comdlg32.inc
includelib	comdlg32.lib

			.data
szCaption	db 'PELock',0
szFilter	db 'Exe Files(*.exe)',0,'*.exe',0,0
szSuccess	db	'success'
			.data?
hFile		dd ?
hMapFile	dd ?
szFileName	db MAX_PATH dup (?)
szFileAddr	dd ?
entryPoint	dd ?
codeSize	dd ?
baseAddr	dd ?
fileAlignment	dd ?
loadLibrary	dd ?
getProcAddr	dd ?
kerBasAddr	dd ?
peBasAddr	dd ?
			.code
;>>>>>>>>>>>>>>>>>>>>>>>
_WinMain	proc
			local @fileName:OPENFILENAME
			
			mov @fileName.lStructSize,sizeof @fileName
			mov @fileName.lpstrFilter,offset szFilter
			mov @fileName.lpstrFile,offset szFileName
			mov @fileName.nMaxFile,MAX_PATH
			mov @fileName.Flags,OFN_FILEMUSTEXIST or OFN_PATHMUSTEXIST
			invoke GetOpenFileName,addr @fileName
			.if eax
				call	_CreateFile
				invoke MessageBoxA,0,addr szFileName,addr szCaption,MB_OK
			.endif
			
			ret
_WinMain 	endp

_CreateFile	proc
			invoke CreateFileA,addr	szFileName,GENERIC_READ or GENERIC_WRITE\
				,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0
			.if eax==INVALID_HANDLE_VALUE
				invoke MessageBoxA,0,addr szSuccess+1,addr szCaption,MB_OK
				ret
			.endif
			mov hFile,eax
			invoke CreateFileMapping,hFile,NULL,PAGE_READWRITE,0,0,NULL
			.if !eax
				invoke MessageBoxA,0,addr szSuccess+2,addr szCaption,MB_OK
				ret
			.endif
			mov hMapFile,eax
			invoke MapViewOfFile,hMapFile,FILE_MAP_WRITE,NULL,NULL,0
			.if eax
				mov szFileAddr,eax
				call _ChangeFile
			.elseif
				invoke MessageBoxA,0,addr szSuccess+3,addr szCaption,MB_OK
			.endif
			ret
_CreateFile endp
			
_ChangeFile	proc
			;>>>>>>>>DOS HEADER
			mov esi,eax
			assume esi:ptr IMAGE_DOS_HEADER
			.if [esi].e_magic !=IMAGE_DOS_SIGNATURE
				ret
			.endif
			;>>>>>>>>DOS HEADER
		
		
			;>>>>>>>>PE HEADER
			add	esi,[esi].e_lfanew
			assume esi:ptr	IMAGE_NT_HEADERS
			.if	[esi].Signature !=IMAGE_NT_SIGNATURE
				ret
			.endif
			;>>>>>>>>PE HEADER
			
			;>>>>>>>>FILE HEADER
			add esi,4
			assume esi:ptr IMAGE_FILE_HEADER
			movsx ebx,[esi].SizeOfOptionalHeader
			
			movsx ecx,[esi].NumberOfSections
			add esi,0014h
			;>>>>>>>>FILE HEADER
			
			;>>>>>>>>OPTIONAL HEADER
			assume esi:ptr IMAGE_OPTIONAL_HEADER32
			mov eax,[esi].ImageBase
			mov baseAddr,eax
			mov eax,[esi].AddressOfEntryPoint
			mov entryPoint,eax
			mov eax,[esi].FileAlignment
			mov fileAlignment,eax
			push esi
			;>>>>>>>>OPTIONAL HEADER
			
			
			;mov edx,CodeEnd
			;sub edx,CodeBegin
			;mov edi,[esi].SizeOfCode
			;add edi,edx
			;mov [esi].SizeofCode,edi

			;>>>>>>>>SECTION HEADER
			add esi,ebx
			;sub esi,
			;add esi,
			;add esi,28h
			assume esi:ptr IMAGE_SECTION_HEADER
			;mov edi,[esi].Characteristics
			;and edi,IMAGE_SCN_CNT_CODE
			;and edi,IMAGE_SCN_MEM_EXECUTE
			;.if edi==IMAGE_SCN_CNT_CODE
			mov edi,[esi].Misc.VirtualSize
			add edi,[esi].PointerToRawData
			add edi,szFileAddr
			
			
			push esi
			mov esi,CodeBegin
			mov ecx,codeSize
			CLD
			rep movsb
			
			pop esi
			
			
			mov eax,[esi].Misc.VirtualSize
			add eax,[esi].VirtualAddress
			pop edx
			assume edx:ptr IMAGE_OPTIONAL_HEADER32
			mov [edx].AddressOfEntryPoint,eax
			
			sub edi,6
			mov eax,entryPoint
			sub eax,01010101h
			;add eax,peBasAddr;00400000h
			add dword ptr [edi],eax	
			
			mov edi,[esi].Misc.VirtualSize
			add edi,codeSize
			mov [esi].Misc.VirtualSize,edi
			
			mov ebx,[esi].SizeOfRawData
			.if edi>ebx
				add ebx,fileAlignment
				mov [esi].SizeOfRawData,ebx
			.endif
			
			
			
			;>>>>>>>>SECTION HEADER
			invoke MessageBoxA,0,addr szSuccess,addr szCaption,MB_OK
			invoke UnmapViewOfFile,szFileAddr
			invoke CloseHandle,hMapFile
			invoke CloseHandle,hFile
			ret
_ChangeFile	endp
;>>>>>>>>>>>>>>>>>>>>>>>
_PswCheck	proc
			ret
_PswCheck 	endp
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
start:
	mov 	edi,CodeEnd
	sub 	edi,CodeBegin
	mov		codeSize,edi
	call 	_WinMain
	call	_PswCheck
	invoke 	ExitProcess,0

	
CodeBegin:
	nop
			nop
			nop
			nop
			nop
			xor eax,eax
			push eax
			sub esp,4
			pushad
			sub esp,30h
		
			push 'naHe'
			push 'ludo'
			push 'MteG'
		; find base addr of kernel32.dll
		ker_bas_add:
		assume fs:nothing 
			xor edx,edx
			mov ecx, dword ptr fs:[edx + 30h] 	; ecx = address of PEB 
			mov ecx, [ecx + 0ch] 		; ecx = pointer to loader data 
			mov ecx, [ecx + 1ch] 		; ecx = first entry in initialisation order list 
			mov ecx, [ecx] 				; ecx = second entry in list (kernel32.dll) 
			mov ecx, [ecx]
			mov ebp, [ecx + 08h] 		; ebp = base address of kernel32.dll 
			;mov kerBasAddr,ebp
			
			;ebp->base address of XX.dll
		exp_tab: 
			mov eax, [ebp + 3ch]		; eax = start of PE header 
			mov ecx, [ebp + eax + 78h]	; ecx = relative offset of export table 
			add ecx, ebp 				; ecx = absolute addr of export table 
			mov ebx, [ecx + 20h] 		; ebx = relative offset of names table 
			add ebx, ebp 				; ebx = absolute addr of names table 
	
			xor edi, edi 				; edi will count through the functions 
			dec edi
		next_function_loop: 
			inc edi 					; increment function counter 
			mov esi, [ebx + edi * 4] 	; esi = relative offset of current function name 
			add esi, ebp 				; esi = absolute addr of current function name 
			cdq 						; dl will hold hash (we know eax is small) 
			mov eax, dword ptr[esi]
			cmp eax,[esp]				
			jnz next_function_loop
			mov eax, dword ptr[esi+4]
			cmp eax,[esp+4]				
			jnz next_function_loop
			mov eax, dword ptr[esi+8]
			cmp eax,[esp+8]				
			jnz next_function_loop
			pop eax
			pop eax
			
		 
			mov ebx, [ecx + 24h] 		; ebx = relative offset of ordinals table 
			add ebx, ebp 				; ebx = absolute addr of ordinals table 
			mov di, [ebx + 2 * edi] 	; di = ordinal number of matched function 
			mov ebx, [ecx + 1ch] 		; ebx = relative offset of address table 
			add ebx, ebp 				; ebx = absolute addr of address table 
			add ebp, [ebx + 4 * edi] 	; add to ebp (base addr of module) the 
										; relative offset of matched function 
			cmp dword ptr [esp-8],'MteG'
			jnz @1
			
			mov [esp+54h],ebp
			sub esp,08h
			push 'Ayra'
			push 'rbiL'
			push 'daoL'
			jmp ker_bas_add
	@1:		cmp dword ptr [esp-8],'daoL'		
			jnz @2
			xor eax,eax
			mov ax,3233h
			push eax
			push 'resu'
			push esp
			call ebp
			;mov loadLibrary,ebp
			mov ebp,eax
			;mov dword ptr [esp+8],'Axo'
			;mov dword ptr [esp+4],'Bega'
			;mov dword ptr [esp],'sseM'
			push 'Axo'
			push 'Bega'
			push 'sseM'
			jmp exp_tab
			
		@2:	;mov getProcAddr,ebp
			add esp,0ch
			xor eax,eax
			push eax
			push '!czc'
			mov ecx,esp
			push eax
			push ecx
			push ecx
			push eax
			call ebp
		;eax->virtual address of the function 
			add esp,48h
			popad
			
			
			nop
			nop
			nop
			nop	
	pop edx
	call edx
	add eax,01010101h
	jmp		eax
CodeEnd:
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.
	end start