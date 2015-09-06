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
szText    db "SEH 程序没有运行",0 

          .code 
start: 
	assume fs:nothing
    lea  eax,[esp-4*2] 
    xchg fs:[0],eax    ;这一行编译错误，哪位大虾指点一下正确格式 
    mov  ebx,offset SEH 
    push ebx 
    push eax 

    mov  esi,0 
    mov  eax,[esi] 
    invoke MessageBox,0,offset szText,offset szCaption,MB_OK 
    jmp  Exit 
SEH: 
    invoke MessageBox,0,offset szTextSEH,offset szCaption,MB_OK 
Exit: 
            invoke ExitProcess,0 
end start 
