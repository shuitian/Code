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
			push 'Ayra'
			push 'rbiL'
			push 'daoL'
		; find base addr of kernel32.dll
		ker_bas_add:
		assume fs:nothing 
			xor edx,edx
			mov ecx, fs:[edx + 30h] 	; ecx = address of PEB 
			mov ecx, [ecx + 0ch] 		; ecx = pointer to loader data 
			mov ecx, [ecx + 1ch] 		; ecx = first entry in initialisation order list 
			mov ecx, [ecx] 				; ecx = second entry in list (kernel32.dll) 
			mov ecx, [ecx]
			mov ebp, [ecx + 08h] 		; ebp = base address of kernel32.dll 
			
			
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
			cmp dword ptr [esp-8],'daoL'
			jnz @f
			
			xor eax,eax
			mov ax,3233h
			push eax
			push 'resu'
			push esp
			call ebp
			mov ebp,eax
			;mov dword ptr [esp+8],'Axo'
			;mov dword ptr [esp+4],'Bega'
			;mov dword ptr [esp],'sseM'
			push 'Axo'
			push 'Bega'
			push 'sseM'
			jmp exp_tab
			
		@@:	xor eax,eax
			push eax
			push 'CCSI'
			mov ecx,esp
			push eax
			push ecx
			push ecx
			push eax
			call ebp
		;eax->virtual address of the function 
			add esp,48h
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