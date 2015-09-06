#include<iostream>
using namespace std;
int main(){
    char key[10000];
    FILE* fpin;
    FILE* fpout; 
    int tmp;
    printf("请输入密钥:\n");
    gets(key);
    
    fpin = fopen("简单文件异或加密_加密后文件.out","r");
    fpout = fopen("简单文件异或加密_解密后文件.out","w");
    
    int k=0;
    while((tmp = fgetc(fpin)) != EOF){
        tmp^=key[k];
        fputc(tmp, fpout);
        k=key[k+1]?(k+1):0;
    }
    
    fclose(fpin);
    fclose(fpout);
    
    system("pause");
    return 0;
}
