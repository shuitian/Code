#include<stdio.h>

void GetGcd(long a,long b){
    if(!b)printf("=%d\n",a);
    else{ 
        printf("=gcd(%d,%d)",b,a%b);
        GetGcd(b,a%b);
    }
}

int main(){
    long t,a,b;
    printf("Please input how many times that you want to try to get the gcd of two numbers:\n");
    scanf("%ld",&t);
    while(t--){
               printf("Please input two numbers:\n");
               scanf("%ld%ld",&a,&b);           
               printf("gcd(%ld,%ld)=",a,b);
               GetGcd(a,b);
    }
    return 0;   
}
