#include<iostream>
using namespace std;
int main(){
    char key[10000];
    FILE* fpin;
    FILE* fpout; 
    int tmp;
    printf("��������Կ:\n");
    gets(key);
    
    fpin = fopen("���ļ�������_���ܺ��ļ�.out","r");
    fpout = fopen("���ļ�������_���ܺ��ļ�.out","w");
    
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
