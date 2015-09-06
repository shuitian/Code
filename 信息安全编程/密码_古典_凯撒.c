#include<stdio.h>
#include<string.h>
#define MaxSize 100
char c_in[MaxSize+1];
void encipher(){
     int i;
     while(1){
        printf("Please input the Plaintext :    (or cin<<\"exit\" to exit!)\nPlaintext : ");
        gets(c_in);
        if((c_in[0]=='e')&&(c_in[1]=='x')&&(c_in[2]=='i')&&(c_in[3]=='t')&&(c_in[4]==0))break;
        else printf("Ciphertext: ");
        for(i=0;c_in[i];i++){
             if(c_in[i]==' ')printf(" ");
             else printf("%c",(c_in[i]-'a'-('A'-'a')*((c_in[i]>='A')&&(c_in[i]<='Z'))+3)%26+'a'+('A'-'a')*((c_in[i]>='A')&&(c_in[i]<='Z')));
        }printf("\n");
     }printf("\n");
}
void decrypt(){
     int i;
     while(1){
        printf("Please input the Ciphertext: (or cin<<\"exit\" to exit!)\nCiphertext: ");
        gets(c_in);
        if((c_in[0]=='e')&&(c_in[1]=='x')&&(c_in[2]=='i')&&(c_in[3]=='t')&&(c_in[4]==0))break;
        else printf("Plaintext : ");
        for(i=0;c_in[i];i++){
             if(c_in[i]==' ')printf(" ");
             else printf("%c",(c_in[i]-'a'-('A'-'a')*((c_in[i]>='A')&&(c_in[i]<='Z'))+23)%26+'a'+('A'-'a')*((c_in[i]>='A')&&(c_in[i]<='Z')));
        }printf("\n");
     }printf("\n");
}
int main(){
    int c;
    while(1){
         printf("Please choose to decrypt or encipher in Caesar Code:\nDecrypt :Press 1\nEncipher :Press 2\nExit :Press 3\n");
         scanf("%d",&c);
         if(c==1){getchar();decrypt();}else if(c==2){getchar();encipher();}else if(c==3)break;
         else printf("Input error, please enter again!\n");
    }return 0;
}
