#include<stdio.h>
#include<windows.h>
int main(){
    FILE *fp=fopen("killself.bat","w");
    fprintf(fp,"@echo off\n");
    fprintf(fp,":start\n");
    fprintf(fp,"if not exist killself.exe goto end\n");
    fprintf(fp,"del killself.exe\n");
    fprintf(fp,"del killself.bat\n");
    fprintf(fp,"goto start\n");
    fprintf(fp,":end\n");
    fclose(fp);
    ShellExecute(NULL,"open","killself.bat",NULL,NULL,SW_HIDE);
    return 0;
}
