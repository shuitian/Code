#include<stdio.h>
int main(){
    char cipherText[] = "nbymywlynjummjblumycmweaodxmmrveppdkusejeluzssjmcao";
    char plainText[] = "nbymywlynjummjblumycmweaodxmmrveppdkusejeluzssjmcao";
    int i,j;
    for(j=0;j<26;j++){
    for(i = 0;i<strlen(cipherText);i++){
        plainText[i]=(cipherText[i]-j-'a'+26)%26+'a';
    }
    printf("%s\n",plainText);
}
    return 0;   
}
