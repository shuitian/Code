/*
     模n剩余类环中部分元素逆元的求解:
     也是单表代替密码乘法密码中的加解密方式 
*/                                
#include<stdio.h>
int is_prime(long long a){
    if(a==2)return 1;
    if(!(a&1))return 0;
    long long i=3;
    for(;i<=a/i;i+=2)if(a%i==0)return 0;
    return 1;
}int main(){
    int n,a,i;
    printf("Enter 0 to exit!\n模n剩余类环中部分元素逆元的求解\n也是单表代替密码乘法密码中的加解密方式:\n");
    while(1){
        printf("Please enter a prime integer:");scanf("%d",&n);
        if(n==0)break;
        if(is_prime(n)){
        scanf("%d",&a);
        for(i=0;i<n;i++){
            if((i*a)%n==1){printf("%d %d\n",a,i);break;}
        }
        }else printf("Input error,please enter again!\n");
    }
    return 0;    
}
