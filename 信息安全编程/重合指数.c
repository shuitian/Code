#include<stdio.h>
#include<string.h>
int main(){
    freopen("重合指数.in","r",stdin);
    freopen("重合指数.out","w",stdout);
    char fp[10000];
    double tf[26]={0.0},ind=0.0;
    int t[26]={0},i,s=0;
    gets(fp);
    for(i=0;fp[i];i++){
        if((fp[i]>='A')&&(fp[i]<='Z')){t[fp[i]-'A']++;s++;}
        else if((fp[i]>='a')&&(fp[i]<='z')){t[fp[i]-'a']++;s++;}
    }for(i=0;i<26;i++){ 
        tf[i]=t[i]/((double)(s));
        ind+=(tf[i]*tf[i]);
    }printf("%4lf\n",ind);
    return 0;   
}
