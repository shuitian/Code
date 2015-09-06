#include<stdio.h>
#include<stdlib.h>
int *is_prime;
int main(){
    FILE *fp=freopen("É¸·¨ÇóËØÊý.txt","w",stdout);
    while(1){
         int t,i,j,k;
         printf("Enter 0 to exit!\nEnter a number less than 10000 to get all the prime that less than the number :\n");
         scanf("%d",&t);
         if(t==0)break;
         is_prime=(int *)malloc((t+1)*sizeof(int));
         if(is_prime){
                for(i=2;i<=t;i++)is_prime[i]=1;
                for(j=2;j*j<=t;j++){
                     if(!is_prime[j])continue;
                     int k=2;
                     while(k*j<=t){
                         is_prime[k*j]=0;k++;
                     }
                }k=0;for(i=2;i<=t;i++)
                if(is_prime[i]){
                    printf("%d,",i);k++;
                }printf("\nThe total number:%d\n",k);
         }else printf("The number is too big!Please enter again!");
         free(is_prime);
    }
}
