#include<stdio.h>  
int main(){  
      printf("Please input how many times that you want to try to get the Factorization of a numbers below 1.0e+8:\n");
      int t,k;  
      long n,i;  
      scanf("%d",&t);  
      while(t--){
             printf("Please input the number to factorize below 1.0e+8:\n");
             scanf("%ld",&n);  
             printf("%ld=",n);  
             if(n==1)printf("1");  
             for(i=2;n!=1;i++){  
                    k=0;  
                    while(n%i==0){  
                      k++;                    
                      n/=i;  
                    }  
                    if(k==1)printf("%ld",i);  
                    else if(k>1)printf("%ld^%d",i,k);  
                    if(n!=1&&k>=1)printf("*");  
             }      
             printf("\n");   
      }  
      return 0;  
}
