#include<stdio.h>
long  f(long a,long b,long m){//a^b mod m
        long s=1;
        while(b){
             if(b&1){s*=a;s%=m;}a*=a;a%=m;s%=m;b/=2;
        }return s;
}void f_7_1(int p){
     int i,count=0;
     for(i=1;i<p;i++){
           if(f(i,(p-1)/2,p)==1){printf("%d ",i);count++;}
     }printf("个数为:%d\n",count);
}int is_prime(long long a){
    if(a==1)return 0;
    if(a==2)return 1;
    if(!(a&1))return 0;
    long long i=3;
    for(;i<=a/i;i+=2)if(a%i==0)return 0;
    return 1;
}
void traversal(int p){
    int *arr=(int *)malloc(p*sizeof(int));
    int count=0;
    memset(arr,0,p*4+4);
//    int arr[p]={0};
if(arr){
    printf("所有p的平方剩余为:");    
    if(p<=1);
    else if(p==3){arr[1]=arr[2]=1;}
    else {
        arr[1]=1;
        int g,c;
        for(g=2;g<p;g++){
            c=f(g,2,p);
            arr[c]=1;
        }
    }for(count=0,arr[0]=1;arr[0]<=p;arr[0]++){
        if(arr[arr[0]]==1)printf("%d ",arr[0]);
        count+=arr[arr[0]];
    }printf("个数为:%d\n",count);
    free(arr);
}
}
int main(){
    int p;
while(1){
    printf("Enter 1 to the Quadratic Reciprocity func!\nEnter 2 to the My new func!\nEnter 0 to exit!\n");
    scanf("%d",&p);
    if(!p)break;
    if(p==1){
        printf("Please input a prime:\n");
        scanf("%d",&p);
        if(is_prime(p)){
            printf("所有p的平方剩余为:");
            f_7_1(p);
        }else printf("The number you inpit is not a prime!\n");
    }else if(p==2){
        printf("Please input an odd number\n");
        scanf("%d",&p);
        if(p&1) traversal(p);
        else printf("Please input an odd number\n");
    }
}
    return 0;   
}
