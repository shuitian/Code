#include<stdio.h>
int main(){
	char c[]="Hello World! \n";
	__asm{
			lea esi,start
			lea edi,end1
			xor eax,eax
start:
			lodsb
			add ah,al
			cmp esi,edi
			jb start
			
			lea esi,c
			mov edi,esi
Repeat:
			lodsb
			or al,al
			jz end1
			xor al,ah
			stosb
			jmp Repeat
end1:
	}
	printf("%s\n",c);
	return 0;
}