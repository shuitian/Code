#include<stdio.h>
int is_prime(long long a){
    if(a==1)return 0;
    if(a==2)return 1;
    if(!(a&1))return 0;
    long long i=3;
    for(;i<=a/i;i+=2)if(a%i==0)return 0;
    return 1;
}
int main(){
    long long a;
    while(scanf("%lld",&a))
    printf("%d\n",is_prime(a));
    return 0;   
}
