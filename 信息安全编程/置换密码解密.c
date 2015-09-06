#include<stdio.h>
int offset(char ch,char *key){
    int i;
    for(i=0;key[i];i++){
        if(key[i]==ch){
            return i+1;
        }
    }
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
//    check(key);
    printf("ciphertext:\n");
    gets(ciphertext);
    printf("ciphertext:%s\n",ciphertext);
    int i,j;
    for(i=0;ciphertext[i];i++){
        if(!isCharacter(ciphertext[i])){
            j=0;    
        }else {
            j=offset(ciphertext[i],key);
        }
        if(j==0){
            plaintext[i]=ciphertext[i];
        }else {
            plaintext[i]=j-1+'a';
        }
    }
    printf("plaintext:%s\n",plaintext);
}
    return 0;   
}
