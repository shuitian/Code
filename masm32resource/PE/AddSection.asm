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

g_szErr                     db "错误",0
g_szDone                    db "文件加密成功!",0
g_szDoneCap                 db "^_^",0
g_szOpenFileFailed          db "打不开文件",0
g_szGetFileSizeFailed       db "获取文件大小失败",0
g_szCreateMapFailed         db "创建文件映射失败",0
g_szMapFileFailed           db "映射文件到内存失败",0
g_szInvalidPE               db "无效的PE文件",0

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

     ;; 这里的dwOrigFileSize 是原始的文件大小
     ;; 因为你要添加新节，所以要多上那么一点                
     ;; 点尺寸.这个尺寸就是APPEND_SIZE,如果                
     ;; 这个尺寸也许会让你最后添加的程序后有                
     ;; 一些多余的数据。也可以没有，不过有一 
     ;; 点点麻烦。这就要计算添加后的
     ;; SizeOfImage了。等到以后讲解吧。
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

    ;; 在建立映射后
    ;; 这段代码将映射后文件的指针存放在局部变量pMem.
    ;; 而指定的NT结构头指针存放到esi寄存器处。
    ;; 现在我们调用添加节函数添加一个新节,AddSection是
    ;; 我们这节的主要函数，将在下面讲解。
    ;; 增加一个新节
    ;; pMem:文件映射内存指针
    ;; g_szNewSectionName:新节的节名,这里是(.new)
    ;; g_dwNewSectionSize:新节的长度,这里是offset EndNewSection - offset NewSection
    invoke AddSection, pMem, offset g_szNewSectionName, g_dwNewSectionSize
    push eax
    mov esi, dwNTHeaderAddr
    assume esi : ptr IMAGE_NT_HEADERS
    ;; 下面做的就是设置新节的中的原代码入口点,就是真正的入口地址.
    mov ebx, dword ptr [esi].OptionalHeader.AddressOfEntryPoint
    add ebx, dword ptr [esi].OptionalHeader.ImageBase
    ;; OrigAddressOfEntry这个变量在CryptFile底部的NewSection节中
    mov eax, offset OrigAddressOfEntry
    mov dword ptr [eax], ebx
    ;; 更新入口点,将新节的入口点设置到NT头结构的AddressOfEntryPoint
    ;; 哪个节的VirusAddress被设置到AddressOfEntryPoint处,哪个节将会被先执行
    ;; 这也是最通常的入口点技术
    pop eax
    assume eax : ptr IMAGE_SECTION_HEADER    
    push dword ptr [eax].VirtualAddress
    pop dword ptr [esi].OptionalHeader.AddressOfEntryPoint
    ;; 下面的代码利用新节节表将新节的代码写入文件
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
;; ----- 新节代码 -----
NewSection:
   ;; 在这里获取地址
   ;; call指令会将下条指令的地址压入堆栈
   ;; 注意此指令的OPCODE为EB00000000
   ;; 病毒与Shellcode等常用此指令定位
   ;; 杀毒软件的启发式搜索常将此特征作为查找特征
   ;; 聪明的读者可以自己修改定位代码来躲过
   ;; 这类的查杀
   call GetEip
   GetEip:
   ;; eax中有保存着当前的地址，标号为GetEip
   pop eax
   add eax, offset OrigAddressOfEntry - offset GetEip
   ;; 两个偏移的差就是这两个地址之间的距离,它的距离 + 起始地址
   ;; 就为OrigAddressOfEntry的地址
   ;; 最后将OrigAddressOfEntry保存的值,也就是原来的入口节的地址
   ;; 送回eax中。
   mov eax, dword ptr [eax]
   ;; 跳到原入口点地址
   jmp eax
;; ----- 新节数据 -----
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
    ;; 将映射地址传给esi,再将esi设置为PE头的地址
    ;; 这里这个3ch是DOS头中e_lfanew的偏移。e_lfanew保存着
    ;; 从MZ头到PE头的偏移,所以这样的相加使esi指向PE头
    ;; 也可以使用下面同等指令替换
    ;; assume esi : ptr IMAGE_DOS_HEADER
    ;; add esi, dword ptr [esi].e_lfanew
    add esi, dword ptr [esi+3ch]
    mov dwNTHeader, esi  
    assume esi : ptr IMAGE_NT_HEADERS
    ;; update the number of section
    mov cx, word ptr [esi].FileHeader.NumberOfSections
    movzx ecx, cx
    ;; 增加节的数目
    inc word ptr [esi].FileHeader.NumberOfSections
    push dword ptr [esi].OptionalHeader.FileAlignment
    pop dwFileAlig
    push dword ptr [esi].OptionalHeader.SectionAlignment
    pop dwSecAlig        
    ;; move esi point to section table
    ;; 在NT头结构下面跟着的就是N个节表街头.加上NT头结构的长度就为第一个节表
    add esi, sizeof IMAGE_NT_HEADERS
    ;; store the last section table
    ;; 在这里保存最后一个节表的偏移,因为一会在计算新节的RVA和offset要应用。
    mov eax, sizeof IMAGE_SECTION_HEADER
    mov ebx, ecx
    imul ebx
    ;; esi 为新节节表的偏移
    ;; 到这里可以判断下SizeOfHeader大小以便检测是否有空间加入新节,这里没有做判断
    ;; 一般没有加过壳的程序都会有空间加入,这个也是按照File Alignment对齐的所以就会有
    ;; 剩余的空隙加入
    add esi, eax                            ; esi = the end of orig last section fva
    push esi
    ;; 这里保存了原最后节表的偏移，为了设置新节的地址做准备
    sub esi, sizeof IMAGE_SECTION_HEADER    ; esi = the orig last section fva
    mov dwLastSecTbl, esi
    pop esi
    ;; set new section table
    ;; 设置新节节表名
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
    ;; 设置设置节的属性,一般关心的有三个属性,读写执行
    ;; 0E00000E0h为设置可读可写可执行三个属性的或运算的值
    ;; 有些杀毒软件的启发式搜索也会检查入口点节是否存在写权限
    ;; 来判断是否被病毒感染,有些多态病毒需要自解密自身所有需要
    ;; 写权限,在壳被恶意程序利用后，现在的杀毒软件有可能报告为
    ;; Heru.XXX或者XCrypt之类，都是启发式惹的祸,过此类检测也是有
    ;; 方法的,例如启动后将的代码写到栈中执行.现在的病毒做的越来越像壳
    ;; 壳整的越来越像病毒,两者只有目的上的区别了。
    push 0E00000E0h
    pop dword ptr [esi].Characteristics
    ;; set section virtualsize
    ;; 这里设置节的真实大小,VirtualSize表示新节的真实大小,没有经过对齐后的
    push dwSectionSize
    pop dword ptr [esi].Misc.VirtualSize
    ;; set section sizeofrawdata
    ;; 节的SizeOfRawData为此节在文件中经过文件对齐后的大小
    ;; PEAlign函数用于计算节对齐后的大小,将在附件的代码中给出
    invoke PEAlign, dwSectionSize, dwFileAlig
    mov dword ptr [esi].SizeOfRawData, eax
    ;; set section virtualaddress
    ;; 设置新节的内存偏移和文件偏移需要上一节的一个信息
    ;; 新节的内存偏移 = 上一节的内存偏移 + 上一节经过节对齐后的长度
    ;; 新节的文件偏移 = 上一节的文件偏移 + 上一节进过文件对齐后的长度
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
    ;; SizeofImage表示从文件到内存映射文件的内容通过节对齐的大小
    ;; 这个值等于当前最后一节的内存偏移 + 当前最后一节的经过节对齐的大小
    ;; 大家可以思考一下。这个值很有用，可以利用此值做一些特殊的感染来躲过启发式
    ;; 搜索。呵呵...
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
    ;; 在这里做一下清0工作ZeroMemory
    mov ecx, dwSectionSize
    xor eax, eax
    cld
    rep stosb
    
    ;; 此函数的返回值,新节节表的文件偏移
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