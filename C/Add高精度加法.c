#include<stdio.h>
#include<string.h>
#define AddMax 1000 
int main(){
    char p1[AddMax+1],p2[1+AddMax],add[AddMax+1];
    int p1p[AddMax+1],p2p[1+AddMax],add1[AddMax+1];
    freopen("Add1.in","r",stdin);
    gets(p1);
    freopen("Add2.in","r",stdin);
    gets(p2);
    freopen("AddResult.out","w",stdout);
    int len1=strlen(p1),len2=strlen(p2),len3=(len1>len2?len1:len2)+1;
    int i,j,k;
    printf("%d %d %d\n",len1,len2,len3);
    for(i=0;2*i<(len1+1);i++){
        char t=p1[i];p1[i]=p1[len1-i-1];p1[len1-1-i]=t;
    }for(i=0;2*i<(len2+1);i++){
        char t=p2[i];p2[i]=p2[len2-i-1];p2[len2-1-i]=t;    
    }for(i=0;i<len3;i++){
        if(p1[i]==' ')p1p[i]=0;
        if(p2[i]==' ')p2p[i]=0;
        p1p[i]=p1[i]-'0';
        p2p[i]=p2[i]-'0';
        add1[i]+=(p1p[i]+p2p[i]);
        add1[i+1]+=(add1[i]/10);
        add1[i]%=10;
    }for(i=0;i<len3;i++){
        printf("%c",p1[i]);   
    }printf("\n");
    for(i=0;i<len3;i++){
        printf("%c",p2[i]);   
    }printf("\n");    
    for(i=0;i<len3;i++){
        add[i]=add1[i]+'0';
    }for(i=0;2*i<(len3+1);i++){
        char t=add[i];add[i]=add[len3-i-1];add[len3-1-i]=t;    
    }
    puts(add);
}
