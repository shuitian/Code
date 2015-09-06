#include<stdio.h>

long GetGcd(long a,long b){
    return b?GetGcd(b,a%b):a;
}

int main(){
    long t,a,b;
    printf("Please input how many times that you want to try to get the gcd of two numbers:\n");
    scanf("%ld",&t);
    while(t--){
               printf("Please input two numbers:\n");
               scanf("%ld%ld",&a,&b);           
               printf("gcd(%ld,%ld)=%ld\n",a,b,GetGcd(a,b));
    }
    return 0;   
}
