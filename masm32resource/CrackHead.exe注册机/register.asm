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
;>>>>>>>>>>>>>>>>>>>>>>>>>>
;数据段
;>>>>>>>>>>>>>>>>>>>>>>>>>
			.data
hInstance	dd		?
hWinMain	dd		?
szCaption	db		"CrackHead",0
szText		db		"注册码为"
szText1		db		10H dup(30h),0
DriTyp		db 		0
VolInf		db		0
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			.code
;>>>>>>>>>>>>>>>>>>>>>>>
_SetReg proc
	pushad
	invoke GetDriveTypeA,0
	mov DriTyp,al
	invoke GetVolumeInformationA,0,0,0,0,0,0b,addr VolInf,0
	lea esi,dword ptr VolInf
	movzx ecx,word ptr DriTyp
	xor edi,edi
@@:	mov eax,ecx
	mov ebx,dword ptr [esi]
	mul ebx
	add edi,eax
	dec ecx
	cmp ecx,0
	jnz	@b
	;xor edi,797a7553h
	mov dword ptr VolInf,edi
	popad
	retn
_SetReg endp
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
start:
	call _SetReg
	invoke MessageBoxA,NULL,addr szText,addr szCaption,0
	invoke	ExitProcess,NULL
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.
	end start