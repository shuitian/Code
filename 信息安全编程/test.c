#include<stdio.h>
#include<string.h>
#define MOD 400000000
int a[MOD];
int main(){

//    memset(a,0,sizeof(a));
    int i,re=1;
    for(i=1;i<MOD;i++){
        re=(re*2)%MOD;
        if(a[re]!=0&&a[re]!=1)a[re]=0;
        if(a[re]==1){
            printf("%d %d\n",i,re);
            break;
        
        }
        //sleep(10);
        printf("%d %d\n",i,re);
        a[re]=1;
    }system("pause");
}
