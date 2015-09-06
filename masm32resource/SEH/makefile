EXE	 = seh2.exe  
OBJS = seh2.obj 
LINK_FLAG=/subsystem:windows 
ML_FLAG= /c /coff 

$(EXE):$(OBJS)
	LINK $(LINK_FLAG) $(CODE_PROP) /out:$(EXE) $(OBJS)
	del *.obj *.res *.bak

.asm.obj:
	ml $(ML_FLAG) $<