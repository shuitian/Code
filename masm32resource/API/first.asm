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
shell_start:
			CLD					; clear flag DF
			;store hash
			push 1e380a6ah		;hash of MessageBoxA
			push 4fd18963h		;hash of ExitProcess
			push 0c917432h		;hash of LoadLibraryA
			mov esi,esp			; esi = addr of first function hash 
			lea edi,[esi-0ch]	; edi = addr to start writing function 

			

			; make some stack space
			xor ebx,ebx
			mov bh, 04h 			 
			sub esp, ebx 
			


			; push a pointer to "user32" onto stack 
			mov bx, 3233h 		; rest of ebx is null 
			push ebx 
			push 72657375h 
			push esp 
			
			xor edx,edx


		; find base addr of kernel32.dll
		assume fs:nothing 
			mov ebx, fs:[edx + 30h] 	; ebx = address of PEB 
			mov ecx, [ebx + 0ch] 		; ecx = pointer to loader data 
			mov ecx, [ecx + 1ch] 		; ecx = first entry in initialisation order list 
			mov ecx, [ecx] 				; ecx = second entry in list (kernel32.dll) 
			mov ecx, [ecx]
			mov ebp, [ecx + 08h] 		; ebp = base address of kernel32.dll 
			
						
		find_lib_functions: 
		
			lodsd 					; load next hash into al and increment esi 
			cmp eax, 1e380a6ah		; hash of MessageBoxA - trigger 
									; LoadLibrary("user32") 
			jne find_functions 
			xchg eax, ebp 			; save current hash 
			call dword ptr [edi - 8h] 		; LoadLibraryA 
			xchg eax, ebp 			; restore current hash, and update ebp 
									; with base address of user32.dll 
			
			
		find_functions: 
			pushad 						; preserve registers 
			mov eax, [ebp + 3ch]		; eax = start of PE header 
			mov ecx, [ebp + eax + 78h]	; ecx = relative offset of export table 
			add ecx, ebp 				; ecx = absolute addr of export table 
			mov ebx, [ecx + 20h] 		; ebx = relative offset of names table 
			add ebx, ebp 				; ebx = absolute addr of names table 
			xor edi, edi 				; edi will count through the functions 

		next_function_loop: 
			inc edi 					; increment function counter 
			mov esi, [ebx + edi * 4] 	; esi = relative offset of current function name 
			add esi, ebp 				; esi = absolute addr of current function name 
			cdq 						; dl will hold hash (we know eax is small) 
			
		hash_loop: 
			movsx eax, byte ptr[esi]
			cmp al,ah
			jz compare_hash
			ror edx,7
			add edx,eax
			inc esi
			jmp hash_loop

		compare_hash:	
			cmp edx, [esp + 1ch] 		; compare to the requested hash (saved on stack from pushad) 
			jnz next_function_loop 
			
		 
			mov ebx, [ecx + 24h] 		; ebx = relative offset of ordinals table 
			add ebx, ebp 				; ebx = absolute addr of ordinals table 
			mov di, [ebx + 2 * edi] 	; di = ordinal number of matched function 
			mov ebx, [ecx + 1ch] 		; ebx = relative offset of address table 
			add ebx, ebp 				; ebx = absolute addr of address table 
			add ebp, [ebx + 4 * edi] 	; add to ebp (base addr of module) the 
										; relative offset of matched function 
			xchg eax, ebp 				; move func addr into eax 
			pop edi 					; edi is last onto stack in pushad 
			stosd 						; write function addr to [edi] and increment edi 
			push edi 
			popad					; restore registers 
					 				; loop until we reach end of last hash 
			cmp eax,1e380a6ah
			jne find_lib_functions 

		function_call:
			xor ebx,ebx
			push  ebx			;// cut string
			push 74736577h
			push 6C696166h		;//push failwest
			mov eax,esp			;//load address of failwest
			push ebx	
			push eax
			push eax
			push ebx
			call dword ptr [edi - 04h] ; //call MessageboxA
			push ebx
			call dword ptr [edi - 08h] ; // call ExitProcess
			ret
shell_end:
			nop
			nop
			nop
			nop		
_WinMain 	endp
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
start:
	call	_WinMain
	invoke ExitProcess,0
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.
	end start