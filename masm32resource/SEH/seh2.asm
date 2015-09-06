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
szTextSEH1  db "堆栈平衡",0 
szTextSEH2  db "堆栈不平衡",0 

          .code 
seh proc

	local data:DWORD 
	lea eax,data
	mov data,eax
	
	assume fs:nothing
    mov ebx,offset SEH
    push ebx
    push fs:[0]
    mov fs:[0],esp

    mov  esi,0 
    mov  eax,[esi] 
    jmp Exit
SEH: 
    invoke MessageBox,0,offset szTextSEH,offset szCaption,MB_OK 
    lea eax,data
	.if data==eax
		invoke MessageBox,0,offset szTextSEH1,offset szCaption,MB_OK 
	.else
		invoke MessageBox,0,offset szTextSEH2,offset szCaption,MB_OK 
	.endif
Exit: 
	invoke ExitProcess,0 
        
seh endp
start:
	call seh
	ret

	end start
