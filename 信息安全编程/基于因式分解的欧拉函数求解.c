#include<stdio.h>
void Euler_1(long n){
             long n1=n,n2=n1,i,k;
             if(n<0)printf("Input error,please enter again!\n");
             else if(n==0);
             else {
                  printf("%ld=",n);
                  for(i=2;n!=1;i++){
                       k=0;  
                       while(n%i==0){  
                            k++;                    
                            n/=i;  
                       }if(k==1)printf("%ld",i);  
                       else if(k>1)printf("%ld^%d",i,k);  
                       if(n!=1&&k>=1)printf("*"); 
                       if(k>=1)n1=n1/i*(i-1);
                  }printf("\nThe Euler's totient function of %ld is %ld\n",n2,n1);
             }
}
int main(){  
      printf("cin<<\"0\" to exit!\n");
      long n;
      while(1){
             printf("Please input a number  below 1.0e+8:\n");
             scanf("%ld",&n);
             Euler_1(n);
      }  
      return 0;  
}
