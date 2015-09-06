#include<stdio.h>
#define MaxSize 100
int r[MaxSize+1];
int q[MaxSize+1];
int out[MaxSize+1];
int ipoint=2,point;
void Get_r_q(int a,int b){//a>b
     r[ipoint]=r[ipoint-2]%r[ipoint-1];
     q[ipoint-1]=r[ipoint-2]/r[ipoint-1];
     if(r[ipoint]!=0){
     printf("%d=%d*%d+%d\n",r[ipoint-2],q[ipoint-1],r[ipoint-1],r[ipoint]);
     ipoint++;
     Get_r_q(r[ipoint-2],r[ipoint-1]);
     }else printf("%d=%d*%d\n",r[ipoint-2],q[ipoint-1],r[ipoint-1]);
}

void opp_output(int ipoint){
     if(ipoint!=1){
     printf("%d=%d-%d*%d\n",r[ipoint],r[ipoint-2],q[ipoint-1],r[ipoint-1]);  
     ipoint--;
     if(ipoint>2)opp_output(ipoint);
     }
}

void expand(){
     int i;
     for(i=0;i<=MaxSize;i++)out[i]=-q[i];
     if(point>=3)printf("%d=",r[ipoint-1]);
     out[ipoint-1]=1;
     out[ipoint]=out[ipoint-2]*(1-out[ipoint-1]);
     point-=2;
     while(point>=1){  
            out[point]=out[point+2]+out[point+1]*out[point];//printf("\n%d %d\n",point,out[point]);
            printf("\n=(%d)*(%d)+(%d)*(%d)",out[point+1],r[point-1],out[point],r[point]);
            point--;
     }printf("\n");
}

int main(){
    long t,a,b;
    printf("Please input how many times that you want to try to get the gcd of two numbers:\n");
    scanf("%ld",&t);
    while(t--){
              printf("Please input two numbers below 1.0e+8:\n");
              scanf("%ld%ld",&a,&b);
              int i;
              long a1=a,b1=b;
              for(i=0;i<=MaxSize;i++)r[i]=0;
              ipoint=2;
              a=a>0?a:-a;b=b>0?b:-b;
              if(a<b){a^=b;b^=a;a^=b;}
              r[0]=a;r[1]=b;
              if((a1==0)&&(b1==0))printf("ERROR!\n");
              else if(a1==0)printf("The gcd of %d and %d is %d\n",a1,b1,b1);
              else if(b1==0)printf("The gcd of %d and %d is %d\n",a1,b1,a1);
              else if(a1%b1==0)printf("The gcd of %d and %d is %d\n",a1,b1,b1);
              else if(b1%a1==0)printf("The gcd of %d and %d is %d\n",a1,b1,a1);
              else {
                   Get_r_q(a,b);point=ipoint;
                   printf("The gcd of %d and %d is %d\n",a1,b1,r[ipoint-1]);
                   opp_output(ipoint-1); 
                   printf("\n");
                   expand();
              }printf("\n");
    }
    return 0;   
}
