EXE=start.exe  
OBJS = start.obj 
LINK_FLAG=/subsystem:windows 
ML_FLAG= /c /coff 
#定义依赖关系和执行命令
$(EXE):$(OBJS)$(RES)
	LINK $(LINK_FLAG) /out:$(EXE) $(OBJS) $(RES)
.asm.obj:
	ml $(ML_FLAG) $<
.rc.res:
	rc $<
clean:
	del *.obj
	del *.res