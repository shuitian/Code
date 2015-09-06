#include<stdio.h>
extern long long  f(long long a,long long b,long long m){//a^b mod m
        long long s=1;
        while(b){
             if(b&1){s*=a;s%=m;}a*=a;a%=m;s%=m;b/=2;
        }return s;
}
int main(){
    long long a,b,m;
    while(1){
          //scanf("%lld%lld%lld",&a,&b,&m);
		  long long  i=0;for(i=0;i<2537;i++){
			a=i;b=13;m=2537;
			long long re=f(a,b,m);
			if(re==981){
				printf("%lld\n",a);
				system("pause");
			}
			printf("%lld\n",re);
			}
    }
}
