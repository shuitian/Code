  .386 
          .model flat,stdcall 
          option casemap:none 
include  kernel32.inc 
include  user32.inc 
include  windows.inc 

includelib  kernel32.lib 
includelib  user32.lib 

          .data 
szCaption  db "SEH",0 
szTextSEH  db "SEH 程序正在运行",0 
szTextSEH1  db "SEH 程序正在第二次运行",0 
szText    db "SEH 程序没有运行",0 

          .code 
start: 
	call mySeh
	ret

mySeh proc
	local data:DWORD
	
	mov data,0
	assume fs:nothing
    lea  eax,[esp-4*2] 
    xchg fs:[0],eax     
    mov  ebx,offset SEH1
    push ebx 
    push eax 
    
    lea  eax,[esp-4*2] 
    xchg fs:[0],eax     
    mov  ebx,offset SEH 
    push ebx 
    push eax 
NEXT:
    mov  esi,0 
    mov  eax,[esi] 
    invoke MessageBox,0,offset szText,offset szCaption,MB_OK 
    jmp  Exit 
SEH1:
	invoke MessageBox,0,offset szTextSEH1,offset szCaption,MB_OK 
	jmp  Exit 
SEH: 
    invoke MessageBox,0,offset szTextSEH,offset szCaption,MB_OK 
	.if data==0
		invoke MessageBox,0,offset szTextSEH,offset szCaption,MB_OK 
	.else
		invoke MessageBox,0,offset szTextSEH1,offset szCaption,MB_OK 
	.endif
Exit: 
            invoke ExitProcess,0 
        
mySeh endp
end start 
