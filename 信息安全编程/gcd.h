#include<stdio.h>
long long  gcd(long long a,long long b){
    return (!b)?a:gcd(b,a%b);  
};
