EXE	 = test.exe  
OBJS = test.obj 
LINK_FLAG=/subsystem:windows 
CODE_PROP=/section:.text,W#�������ο�д
ML_FLAG= /c /coff 

$(EXE):$(OBJS)
	LINK $(LINK_FLAG) $(CODE_PROP) /out:$(EXE) $(OBJS)
	del *.obj *.res *.bak

.asm.obj:
	ml $(ML_FLAG) $<