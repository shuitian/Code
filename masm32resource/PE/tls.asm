.386
.model flat,stdcall
option casemap:none
include		windows.inc
include		user32.inc
includelib	user32.lib
include		kernel32.inc
includelib	kernel32.lib


.data
szText db 'HelloTls'
Tls1	dd	0
TlsCallBack	dd	offset	TLS
PUBLIC _tls_used
_tls_used IMAGE_TLS_DIRECTORY <Tls1, Tls1, Tls1, TlsCallBack, 0, ?>		

			.code

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
start:
	invoke	ExitProcess,NULL
	RET

TLS:
	invoke	MessageBox,NULL,addr szText,NULL,MB_OK
	RET
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.
	end start