.386
.model flat,stdcall
option casemap:none
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; include 文件定义
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
include		windows.inc
include		user32.inc
include		kernel32.inc

includelib	user32.lib
includelib	kernel32.lib
;>>>>>>>>>>>>>>>>>>>>>>>>>>
;数据段
;>>>>>>>>>>>>>>>>>>>>>>>>>
			.const
szCaption	db		'My First Window!',0
szText		db		'Hello,World!',0
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;code segment
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			.code
;>>>>>>>>>>>>>>>>>>>>>>>
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>..
_WinMain		proc
			invoke MessageBoxA,0,addr szText,addr szCaption,MB_OK
			ret
_WinMain 	endp
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
start:
	call	_WinMain
	invoke	ExitProcess,NULL
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.
	end start