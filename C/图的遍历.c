#include<stdio.h>
int main(){
    int bo[303]={0};
    int t,a,b,n,i,s,f;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        if(n<1)f=0;
        else if(n==1)f=1;
        else {scanf("%d",&a);
        f=1;
        for(i=0;i<303;i++)bo[i]=0;
        for(i=1;i<n;i++){
            scanf("%d",&b);
            s=a>b?(a-b):(b-a);//printf("%d ",s);
            if(s>301){f=0;break;}
            bo[s]=1;
            a=b;
        }if(f){for(i=1;i<n;i++){
            //printf("%d ",f);
            if(!bo[i]){f=0;break;}
            //printf("%d ",f);
        }
    }
        }
        //for(i=0;i<10;i++)printf("\nbo[%d]:%d",i,bo[i]);
        if(f){printf("Jolly\n");}
        else printf("Not jolly\n");
    }
    return 0;
}
