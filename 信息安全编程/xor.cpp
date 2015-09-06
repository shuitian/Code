#include<iostream>
using namespace std;
int main(int argc,char *argv[]){
    if(argc!=2){
        printf("please input 2 argument!\n");
        system("pause");
        return 0;
    }
    FILE* fpin;
    FILE* fpout;
    char in[10]="xor.in",out[10]="xor.e";
    if(argv[1][0]=='-' && argv[1][1]=='e');
    else if(argv[1][0]=='-' && argv[1][1]=='d'){
        in[4]='e';
        in[5]=0;
        out[4]='d';
    }else {
        printf("input -d or -e\n");
        system("pause");
        return 0;
    }
    fpin=fopen(in,"r");
    fpout=fopen(out,"w");
    if(!fpin){
        printf("cannot open file %s\n",in);
        system("pause");
        return 0;
    }if(!fpout){
        printf("cannot open file %s\n",out);
        system("pause");
        return 0;
    }
    //printf("%s %s\n",in,out);
    char key[10000];
    int tmp;
    printf("Please input the key:\n");
    gets(key);
    int k=0;
    while((tmp = fgetc(fpin)) != EOF){
        tmp^=key[k];
        fputc(tmp, fpout);
        k=key[k+1]?(k+1):0;
    }
    fclose(fpin);
    fclose(fpout);
    system(out);
    return 0;
}
