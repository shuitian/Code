#include<stdio.h>
#define MaxSize 100
int r[MaxSize+1];
int q[MaxSize+1];
int ipoint=2;
void Get_r_q(int a,int b){//a>b
     r[ipoint]=r[ipoint-2]%r[ipoint-1];
     q[ipoint-1]=r[ipoint-2]/r[ipoint-1];
     if(r[ipoint]!=0){
     printf("%d=%d*%d+%d\n",r[ipoint-2],q[ipoint-1],r[ipoint-1],r[ipoint]);
     ipoint++;
     Get_r_q(r[ipoint-2],r[ipoint-1]);
     }else printf("%d=%d*%d\n",r[ipoint-2],q[ipoint-1],r[ipoint-1]);
}

int main(){
    long t,a,b;
    printf("Please input how many times that you want to try to get the gcd of two numbers:\n");
    scanf("%ld",&t);
    while(t--){
              printf("Please input two numbers:\n");
              scanf("%ld%ld",&a,&b);
              int i;
              long a1=a,b1=b;
              for(i=0;i<=MaxSize;i++)r[i]=0;
              ipoint=2;
              a=a>0?a:-a;b=b>0?b:-b;
              if(a<b){a^=b;b^=a;a^=b;}
              r[0]=a;r[1]=b;
              Get_r_q(a,b);
              printf("The gcd of %d and %d is %d\n",a1,b1,r[ipoint-1]);
    }
    return 0;   
}
