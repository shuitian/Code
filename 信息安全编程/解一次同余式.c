#include<stdio.h>
#include"gcd.h"
int main(){
    int a,b,p,s;
    while(1){
        printf("Please intput three number:解一次同余式ax与b模p同余ax=b(mod p)");   
        scanf("%d%d%d",&a,&b,&p);
        s=gcd(a,p);
        if(b%s){
            a/=s;b/=s;p/=s;
            
        }else printf("There is no x exit!\n");
    }
}
