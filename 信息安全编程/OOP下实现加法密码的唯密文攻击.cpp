#include<iostream> 
#define MaxSize 100
using namespace std;
class decrypt{
      public:
             decrypt(char *f){
                  int i;
                  for(i=0;i<=strlen(f);i++)c[i]=f[i];
             }void do_decrypt(int p){
                 int i;
                 for(i=0;i<strlen(c);i++){
                     m[p][i]=((c[i]+p-'a')%26)+'a';
                     printf("%c",m[p][i]);
                 }printf("\n");
             }void show(){
                   int i;
                   for(i=0;i<26;i++){
                      printf("If the key is %.2d : the plaintext is :",i);
                      do_decrypt(i);
                   }
             }char *get_c(){
                  return c;
             }char *get_m(int p){
                   return m[p];
             }
      private:
              char c[MaxSize+1];
              char m[26][MaxSize+1];
};
int main(){
    while(1){
         char *in=(char *)malloc((MaxSize+1)*sizeof(char));
         if(in){
         scanf("%s",in);
         decrypt text(in);
         text.show();
         free(in);
         }
    }
    return 0;
}
