#include<stdio.h>
#include<string.h>
int main(){
    freopen("频率统计.in","r",stdin);
    freopen("频率统计.out","w",stdout);
    int i,t[36]={0},s=0,max,maxi;
    char fp[10000];
    double tf[26]={0.0};
    gets(fp);
    for(i=0;fp[i]/*||(fp[i]==' ')*/;i++){
        if((fp[i]>='A')&&(fp[i]<='Z')){t[fp[i]-'A']++;s++;}
        else if((fp[i]>='a')&&(fp[i]<='z')){t[fp[i]-'a']++;s++;}
        else if((fp[i]>='0')&&(fp[i]<='9')){t[fp[i]-'0'+26]++;s++;}
    }   for(i=0;i<36;i++)tf[i]=t[i]/((double)(s));
        printf("全频率表:\n");
        for(i=0;i<26;i++){
            printf("%c:%3d  %.4f\n",'a'+i,t[i],tf[i]);
        }for(i=26;i<36;i++){
            printf("%c:%3d  %.4f\n",'0'+i-26,t[i],tf[i]);
        }
        printf("降序频率统计表:\n");
        maxi=-2;
        while(maxi!=-1){
            maxi=-1;max=0;
            for(i=0;i<36;i++){if((t[i]>max)&&(t[i]!=0)){max=t[i];maxi=i;}}
            if(maxi>=0)
                if(maxi<26)
                    printf("%c:%3d  %.4lf\n",'a'+maxi,max,tf[maxi]);
                else 
                    printf("%c:%3d  %.4lf\n",'0'+maxi-26,max,tf[maxi]);
            t[maxi]=0;
        }
    return 0;   
}
