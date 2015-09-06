#include<stdio.h>
#include<string.h>
#define MaxKey 100
#define MaxSize 100
char key[MaxKey+1];
char plaintext[MaxSize+1];
char ciphertext[MaxSize+1];
void encrypt(char *key,char *plaintext){
     int i,fkey;
     for(i=fkey=0;plaintext[i];i++,fkey++)
         if(plaintext[i]==' '){ciphertext[i]=' ';printf(" ");fkey--;}
         else if(plaintext[i]!=' '){
             ciphertext[i]=(key[fkey%strlen(key)]-'A'+plaintext[i]-'A')%26+'A';
             printf("%c",ciphertext[i]);
         }
}
void decrypt(char *key,char *ciphertext){
     int i,fkey;
     for(i=fkey=0;ciphertext[i];i++,fkey++)
         if(ciphertext[i]==' '){plaintext[i]=' ';printf(" ");fkey--;}
         else if(ciphertext[i]!=' '){
             plaintext[i]=(-key[fkey%strlen(key)]+'A'+ciphertext[i]+26-'A')%26+'A';
             printf("%c",plaintext[i]);
         }
}
int main(){
    int number;
    while(1){
    printf("enter 1 to encrypt\nenter 2 to decrypt\nenter 3 to exit!\n");
    scanf("%d",&number);
    if(number==1){
          printf("Please input the key in capital letters without blank space!\n");       
          scanf("%s",&key);getchar();
          printf("Please input the plaintext in capital letters without blank space!\n");
          gets(plaintext);
          printf("The ciphertext is ");
          encrypt(key,plaintext);
          printf("\n");
    }else if(number==2){
          printf("Please input the key in capital letters without blank space!\n"); 
          scanf("%s",&key);getchar();
          printf("Please input the ciphertext in capital letters without blank space!\n");
          gets(ciphertext);
          printf("The plaintext is ");
          decrypt(key,ciphertext);
          printf("\n");
    }else if(number==3)break;
    else printf("Input error,please enter again!\n");
}
    return 0;
}
