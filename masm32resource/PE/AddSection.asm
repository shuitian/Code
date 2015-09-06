.386
.model flat, stdcall
option casemap:none

;; ----------------------------------------
;; header file and lib file
;; ----------------------------------------
include \masm32\include\kernel32.inc
include \masm32\include\user32.inc

includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\user32.lib

include \masm32\include\windows.inc

;; ----------------------------------------
;; value definition
;; ----------------------------------------
APPEND_SIZE                     equ 2000h
;; ----------------------------------------
;; const definition
;; ----------------------------------------
.const
g_szTargetFile              db 'target.exe',0
g_szNewSectionName          db ".wow",0

g_szErr                     db "����",0
g_szDone                    db "�ļ����ܳɹ�!",0
g_szDoneCap                 db "^_^",0
g_szOpenFileFailed          db "�򲻿��ļ�",0
g_szGetFileSizeFailed       db "��ȡ�ļ���Сʧ��",0
g_szCreateMapFailed         db "�����ļ�ӳ��ʧ��",0
g_szMapFileFailed           db "ӳ���ļ����ڴ�ʧ��",0
g_szInvalidPE               db "��Ч��PE�ļ�",0

;; ----------------------------------------
;; data segment
;; ----------------------------------------
.data
g_bError                db 0
g_dwNewSectionSize      dd 0
;; ----------------------------------------
;; function statement
;; ----------------------------------------
PEAlign proto dwTarNum : DWORD, dwAlignTo : DWORD
CryptFile proto szFname : LPSTR
AddSection proto pMem : LPVOID, 
                 pSectionName : LPVOID, 
                 dwSectionSize : DWORD
;; ----------------------------------------
;; code segment
;; ----------------------------------------
.code
Start:
    invoke CryptFile, offset g_szTargetFile
    invoke ExitProcess, 1
    
    
CryptFile proc szFname : LPSTR    
     LOCAL hFile : HANDLE
     LOCAL hMap : HANDLE
     LOCAL pMem : LPVOID
     LOCAL dwOrigFileSize : DWORD
     LOCAL dwNTHeaderAddr : DWORD
     
     ;; init data
     xor eax, eax
     mov g_bError, al
     mov eax, offset EndNewSection - offset NewSection
     mov g_dwNewSectionSize, eax
     
     ;; open file
      invoke CreateFile, szFname,\
                          GENERIC_WRITE + GENERIC_READ,\
                          FILE_SHARE_WRITE + FILE_SHARE_READ,\
                          NULL,\
                          OPEN_EXISTING,\
                          FILE_ATTRIBUTE_NORMAL,\
                          0
     .IF eax == INVALID_HANDLE_VALUE
         jmp OpenFileFailed                
     .ENDIF
     mov hFile, eax 
     invoke GetFileSize, hFile, NULL
    .IF eax == 0
        invoke CloseHandle, hFile  
        jmp GetFileSizeFailed
    .ENDIF
     mov dwOrigFileSize, eax   

     ;; �����dwOrigFileSize ��ԭʼ���ļ���С
     ;; ��Ϊ��Ҫ����½ڣ�����Ҫ������ôһ��                
     ;; ��ߴ�.����ߴ����APPEND_SIZE,���                
     ;; ����ߴ�Ҳ������������ӵĳ������                
     ;; һЩ��������ݡ�Ҳ����û�У�������һ 
     ;; ����鷳�����Ҫ������Ӻ��
     ;; SizeOfImage�ˡ��ȵ��Ժ󽲽�ɡ�
     add eax, APPEND_SIZE

     xchg eax, ecx
     ;; create memory map
     xor ebx, ebx     
     invoke CreateFileMapping, hFile, ebx, PAGE_READWRITE, ebx, ecx, ebx
     .IF eax == 0
         invoke CloseHandle, hFile
         jmp CreateMapFailed                
     .ENDIF
     mov hMap, eax
     ;; map file to memory
     invoke MapViewOfFile, hMap,
                           FILE_MAP_WRITE+FILE_MAP_READ+FILE_MAP_COPY, 
                           ebx, ebx, ebx
     .IF eax == 0
         invoke CloseHandle, hMap
         invoke CloseHandle, hFile
         jmp MapFileFailed
     .ENDIF
     mov pMem, eax                               
     ;; check it's PE file or not ?
     xchg eax, esi
     assume esi : ptr IMAGE_DOS_HEADER
     .IF [esi].e_magic != 'ZM'
         invoke UnmapViewOfFile, pMem
         invoke CloseHandle, hMap
         invoke CloseHandle, hFile
         jmp InvalidPE        
     .ENDIF       
     add esi, [esi].e_lfanew
     assume esi : ptr IMAGE_NT_HEADERS   
     .IF word ptr [esi].Signature != 'EP'
         invoke UnmapViewOfFile, pMem
         invoke CloseHandle, hMap
         invoke CloseHandle, hFile
         jmp InvalidPE        
     .ENDIF
     mov dwNTHeaderAddr, esi

    ;; �ڽ���ӳ���
    ;; ��δ��뽫ӳ����ļ���ָ�����ھֲ�����pMem.
    ;; ��ָ����NT�ṹͷָ���ŵ�esi�Ĵ�������
    ;; �������ǵ�����ӽں������һ���½�,AddSection��
    ;; ������ڵ���Ҫ�������������潲�⡣
    ;; ����һ���½�
    ;; pMem:�ļ�ӳ���ڴ�ָ��
    ;; g_szNewSectionName:�½ڵĽ���,������(.new)
    ;; g_dwNewSectionSize:�½ڵĳ���,������offset EndNewSection - offset NewSection
    invoke AddSection, pMem, offset g_szNewSectionName, g_dwNewSectionSize
    push eax
    mov esi, dwNTHeaderAddr
    assume esi : ptr IMAGE_NT_HEADERS
    ;; �������ľ��������½ڵ��е�ԭ������ڵ�,������������ڵ�ַ.
    mov ebx, dword ptr [esi].OptionalHeader.AddressOfEntryPoint
    add ebx, dword ptr [esi].OptionalHeader.ImageBase
    ;; OrigAddressOfEntry���������CryptFile�ײ���NewSection����
    mov eax, offset OrigAddressOfEntry
    mov dword ptr [eax], ebx
    ;; ������ڵ�,���½ڵ���ڵ����õ�NTͷ�ṹ��AddressOfEntryPoint
    ;; �ĸ��ڵ�VirusAddress�����õ�AddressOfEntryPoint��,�ĸ��ڽ��ᱻ��ִ��
    ;; ��Ҳ����ͨ������ڵ㼼��
    pop eax
    assume eax : ptr IMAGE_SECTION_HEADER    
    push dword ptr [eax].VirtualAddress
    pop dword ptr [esi].OptionalHeader.AddressOfEntryPoint
    ;; ����Ĵ��������½ڽڱ��½ڵĴ���д���ļ�
    mov esi, offset NewSection
    mov edi, dword ptr [eax].PointerToRawData
    add edi, pMem
    mov ecx, g_dwNewSectionSize
    cld
    rep movsb
 LogicShellExit:
     ;; close handle & write it
     invoke UnmapViewOfFile, pMem
     invoke CloseHandle, hMap
     invoke CloseHandle, hFile
     .IF g_bError == 0
         ;; show success message  
         invoke MessageBox, NULL, offset g_szDone, offset g_szDoneCap, MB_ICONINFORMATION
     .ENDIF        
     ret
;; ----- Show error message ----- 
OpenFileFailed:
     lea eax, g_szOpenFileFailed
     jmp ShowErr
GetFileSizeFailed:
     lea eax, g_szGetFileSizeFailed
     jmp ShowErr    
CreateMapFailed:
     lea eax, g_szCreateMapFailed
     jmp ShowErr
MapFileFailed:
     lea eax, g_szMapFileFailed
     jmp ShowErr        
InvalidPE:          
     lea eax, g_szInvalidPE
     jmp ShowErr   
ShowErr:
     invoke MessageBox, NULL, eax, offset g_szErr, MB_ICONERROR
     mov al, 1
     mov g_bError, al
     jmp LogicShellExit
;; ----- �½ڴ��� -----
NewSection:
   ;; �������ȡ��ַ
   ;; callָ��Ὣ����ָ��ĵ�ַѹ���ջ
   ;; ע���ָ���OPCODEΪEB00000000
   ;; ������Shellcode�ȳ��ô�ָ�λ
   ;; ɱ�����������ʽ����������������Ϊ��������
   ;; �����Ķ��߿����Լ��޸Ķ�λ���������
   ;; ����Ĳ�ɱ
   call GetEip
   GetEip:
   ;; eax���б����ŵ�ǰ�ĵ�ַ�����ΪGetEip
   pop eax
   add eax, offset OrigAddressOfEntry - offset GetEip
   ;; ����ƫ�ƵĲ������������ַ֮��ľ���,���ľ��� + ��ʼ��ַ
   ;; ��ΪOrigAddressOfEntry�ĵ�ַ
   ;; ���OrigAddressOfEntry�����ֵ,Ҳ����ԭ������ڽڵĵ�ַ
   ;; �ͻ�eax�С�
   mov eax, dword ptr [eax]
   ;; ����ԭ��ڵ��ַ
   jmp eax
;; ----- �½����� -----
OrigAddressOfEntry  dd ?

EndNewSection:

CryptFile endp 

AddSection proc uses ebx ecx edx esi edi, pMem : LPVOID,
                                          pSectionName : LPVOID,
                                          dwSectionSize : DWORD
;; add a new section
;; ret: eax =  new section table file offset
    LOCAL dwNTHeader : LPVOID
    LOCAL dwLastSecTbl : LPVOID    
    LOCAL dwFileAlig : DWORD
    LOCAL dwSecAlig : DWORD
    
    ;; move to section table
    mov esi, pMem
    ;; ��ӳ���ַ����esi,�ٽ�esi����ΪPEͷ�ĵ�ַ
    ;; �������3ch��DOSͷ��e_lfanew��ƫ�ơ�e_lfanew������
    ;; ��MZͷ��PEͷ��ƫ��,�������������ʹesiָ��PEͷ
    ;; Ҳ����ʹ������ͬ��ָ���滻
    ;; assume esi : ptr IMAGE_DOS_HEADER
    ;; add esi, dword ptr [esi].e_lfanew
    add esi, dword ptr [esi+3ch]
    mov dwNTHeader, esi  
    assume esi : ptr IMAGE_NT_HEADERS
    ;; update the number of section
    mov cx, word ptr [esi].FileHeader.NumberOfSections
    movzx ecx, cx
    ;; ���ӽڵ���Ŀ
    inc word ptr [esi].FileHeader.NumberOfSections
    push dword ptr [esi].OptionalHeader.FileAlignment
    pop dwFileAlig
    push dword ptr [esi].OptionalHeader.SectionAlignment
    pop dwSecAlig        
    ;; move esi point to section table
    ;; ��NTͷ�ṹ������ŵľ���N���ڱ��ͷ.����NTͷ�ṹ�ĳ��Ⱦ�Ϊ��һ���ڱ�
    add esi, sizeof IMAGE_NT_HEADERS
    ;; store the last section table
    ;; �����ﱣ�����һ���ڱ��ƫ��,��Ϊһ���ڼ����½ڵ�RVA��offsetҪӦ�á�
    mov eax, sizeof IMAGE_SECTION_HEADER
    mov ebx, ecx
    imul ebx
    ;; esi Ϊ�½ڽڱ��ƫ��
    ;; ����������ж���SizeOfHeader��С�Ա����Ƿ��пռ�����½�,����û�����ж�
    ;; һ��û�мӹ��ǵĳ��򶼻��пռ����,���Ҳ�ǰ���File Alignment��������Ծͻ���
    ;; ʣ��Ŀ�϶����
    add esi, eax                            ; esi = the end of orig last section fva
    push esi
    ;; ���ﱣ����ԭ���ڱ��ƫ�ƣ�Ϊ�������½ڵĵ�ַ��׼��
    sub esi, sizeof IMAGE_SECTION_HEADER    ; esi = the orig last section fva
    mov dwLastSecTbl, esi
    pop esi
    ;; set new section table
    ;; �����½ڽڱ���
    assume esi : ptr IMAGE_SECTION_HEADER
    ;; set section name
    push esi
    lea edi, [esi].Name1
    mov esi, pSectionName
CopySectionNameLoop:   
    lodsb
    test al, al
    jz EndCopySectionNameLoop
    stosb
    jmp CopySectionNameLoop
EndCopySectionNameLoop:  
    pop esi  
    ;; set section characteristics
    ;; �������ýڵ�����,һ����ĵ�����������,��дִ��
    ;; 0E00000E0hΪ���ÿɶ���д��ִ���������ԵĻ������ֵ
    ;; ��Щɱ�����������ʽ����Ҳ������ڵ���Ƿ����дȨ��
    ;; ���ж��Ƿ񱻲�����Ⱦ,��Щ��̬������Ҫ�Խ�������������Ҫ
    ;; дȨ��,�ڿǱ�����������ú����ڵ�ɱ������п��ܱ���Ϊ
    ;; Heru.XXX����XCrypt֮�࣬��������ʽ�ǵĻ�,��������Ҳ����
    ;; ������,���������󽫵Ĵ���д��ջ��ִ��.���ڵĲ�������Խ��Խ���
    ;; ������Խ��Խ�񲡶�,����ֻ��Ŀ���ϵ������ˡ�
    push 0E00000E0h
    pop dword ptr [esi].Characteristics
    ;; set section virtualsize
    ;; �������ýڵ���ʵ��С,VirtualSize��ʾ�½ڵ���ʵ��С,û�о���������
    push dwSectionSize
    pop dword ptr [esi].Misc.VirtualSize
    ;; set section sizeofrawdata
    ;; �ڵ�SizeOfRawDataΪ�˽����ļ��о����ļ������Ĵ�С
    ;; PEAlign�������ڼ���ڶ����Ĵ�С,���ڸ����Ĵ����и���
    invoke PEAlign, dwSectionSize, dwFileAlig
    mov dword ptr [esi].SizeOfRawData, eax
    ;; set section virtualaddress
    ;; �����½ڵ��ڴ�ƫ�ƺ��ļ�ƫ����Ҫ��һ�ڵ�һ����Ϣ
    ;; �½ڵ��ڴ�ƫ�� = ��һ�ڵ��ڴ�ƫ�� + ��һ�ھ����ڶ����ĳ���
    ;; �½ڵ��ļ�ƫ�� = ��һ�ڵ��ļ�ƫ�� + ��һ�ڽ����ļ������ĳ���
    mov eax, dwLastSecTbl                       ; eax = orig last section table fva
    assume eax : ptr IMAGE_SECTION_HEADER
    mov ecx, dword ptr [eax].VirtualAddress
    add ecx, dword ptr [eax].Misc.VirtualSize        ; ecx = new section rva
    mov ebx, dword ptr [eax].PointerToRawData
    add ebx, dword ptr [eax].SizeOfRawData           ; ebx = new section fva
    invoke PEAlign, ecx, dwSecAlig
    mov dword ptr [esi].VirtualAddress, eax
    ;; set section pointertorawdata
    invoke PEAlign, ebx, dwFileAlig
    mov dword ptr [esi].PointerToRawData, eax
    ;; update the sizeofimage
    ;; SizeofImage��ʾ���ļ����ڴ�ӳ���ļ�������ͨ���ڶ���Ĵ�С
    ;; ���ֵ���ڵ�ǰ���һ�ڵ��ڴ�ƫ�� + ��ǰ���һ�ڵľ����ڶ���Ĵ�С
    ;; ��ҿ���˼��һ�¡����ֵ�����ã��������ô�ֵ��һЩ����ĸ�Ⱦ���������ʽ
    ;; �������Ǻ�...
    mov eax, dword ptr [esi].VirtualAddress
    add eax, dword ptr [esi].Misc.VirtualSize
    invoke PEAlign, eax, dwSecAlig
    mov edx, dwNTHeader
    assume edx : ptr IMAGE_NT_HEADERS
    mov dword ptr [edx].OptionalHeader.SizeOfImage, eax
    push dword ptr [esi].PointerToRawData
    pop edi
    add edi, pMem
    ;; clear the new sec
    ;; ��������һ����0����ZeroMemory
    mov ecx, dwSectionSize
    xor eax, eax
    cld
    rep stosb
    
    ;; �˺����ķ���ֵ,�½ڽڱ���ļ�ƫ��
    mov eax, esi
    assume esi : nothing
    assume eax : nothing
    assume edx : nothing
    ret
AddSection endp
   
PEAlign proc uses ecx edx, dwTarNum : DWORD, dwAlignTo : DWORD
;; returns aligned value    
    ;; Algorithms:
    ;; $1 = dwTarNum / dwAlignTo
    ;; if remain != 0
    ;; $r = $1 + 1 * dwAlignTo
    ;; return $r
    mov ecx, dwAlignTo
    mov eax, dwTarNum
    xor edx, edx
    div ecx
    cmp edx, 0
    jz AlreadyAligned
    inc eax
AlreadyAligned:
    mul ecx      
    ret

PEAlign endp   
    
end Start