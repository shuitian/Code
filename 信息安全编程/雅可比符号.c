#include<stdio.h>
int is_prime(int a){
    if(a==1)return 0;
    if(a==2)return 1;
    if(!(a&1))return 0;
    int i=3;
    for(;i<=a/i;i+=2)if(a%i==0)return 0;
    return 1;
}
int jacobi(int up,int down){
    up%=down;
    if(up==1)return 1;
    if(!up)return 0;
    else if(!(down&1)){
        down/=2;
        if(!(up&1))return 0;
        else return (jacobi(up,down));
    }else {
        int i;
        if(is_prime(down)){
            if(up==1)return 1;
            else if(up==2)return (1&((down*down-1)/8))?-1:1;
            else if(is_prime(up)){
                int s;
                if((1&((up-1)/2))&&(1&((down-1)/2)))s=-1;
                else s=1;
                return s*jacobi(down,up);
            }else {
                for(i=2;i<up;i++){
                    if(up%i==0){
                        up/=i;
                        return jacobi(up,down)*jacobi(i,down);
                    }
                }
            }
        }else for(i=3;i<down;i++){
            if(down%i==0){down/=i;return jacobi(up,i)*jacobi(up,down);}
        }
    }return 1;
}
int main(){
    int up,down;
    while(1){
        printf("Please input two numbers:jacobi(up/down)\n");
        scanf("%d%d",&up,&down);
        printf("%d\n",jacobi(up,down));
    }
    return 0;   
}
