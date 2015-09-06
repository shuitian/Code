#include<stdio.h>
int offset(char ch){
    if(ch >='a' && ch<='z')return ch-'a';
    if(ch >='A' && ch<='Z')return ch-'A';
    return 0;
}
int isCharacter(char ch){
    return (ch>='a' && ch <='z' )|| (ch >= 'A' && ch<= 'Z');
}
void check(char *key){
    int i;
    for(i=0;key[i];i++){
        if(!isCharacter(key[i])){
            printf("Error at [%d]\n",i);
            exit(0);
        }
    }
}
int main(){
    char key[26],plaintext[1000],ciphertext[1000];
while(1){
    memset(key,0,sizeof(key));
    memset(plaintext,0,sizeof(plaintext));
    memset(ciphertext,0,sizeof(ciphertext));
    printf("key:");
    gets(key);
    printf("%s\n",key);
    check(key);
    printf("plaintext:\n");
    gets(plaintext);
    printf("%s\n",plaintext);
    int i,j;
    for(i=0;plaintext[i];i++){
        if(!isCharacter(plaintext[i])){
            j=0;    
        }else {
            j=key[offset(plaintext[i])];
        }
        if(j==0){
            ciphertext[i]=plaintext[i];
        }else {
            ciphertext[i]=key[offset(plaintext[i])];
        }
    }
    printf("ciphertext:%s\n",ciphertext);
}
    return 0;   
}
