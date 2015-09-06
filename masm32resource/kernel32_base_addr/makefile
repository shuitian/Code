#nmake test
EXE=kernel32_base_addr.exe  #指定输出文件
OBJS = kernel32_base_addr.obj  #需要的目标文件
LINK_FLAG=/subsystem:windows #链接选项
CODE_PROP=/section:.text,W#定义代码段可写
EXE_BASE=/base:0x00500000
ML_FLAG= /c /coff #编译选项

#定义依赖关系和执行命令
$(EXE):$(OBJS)$(RES)
	LINK $(LINK_FLAG) $(CODE_PROP) /out:$(EXE) $(OBJS)
	
#定义汇编编译和资源编译的默认规则
.asm.obj:
	ml $(ML_FLAG) $<
	
#清楚临时文件
clean:
	del *.obj