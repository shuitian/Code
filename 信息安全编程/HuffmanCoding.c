#include<stdio.h>
typedef struct Node{
    char c;
    int value;
    int flag;
    struct Node *left,*right,*parent;
}node;
int main(){
    while(1){
    char in[100],haff[26][100],c;
    int num[26]={0},i,j,k,max=0,n=0,len,hafflen[26]={0};
    node Tnode[52];
    gets(in);
    len=strlen(in);
    for(i=0;i<len;i++){
        if((in[i]>='a') && (in[i]<='z')){
             num[in[i]-'a']++;
        }else if((in[i]>='A') && (in[i]<='Z')){
            num[in[i]-'A']++;   
        }
    }for(i=0;i<52;i++){
        Tnode[i].flag=0;
        Tnode[i].left=Tnode[i].right=Tnode[i].parent=NULL;
        Tnode[i].c=Tnode[i].value=0;
    }
    for(i=0;i<26;i++){
        if(num[i]>0){
            n++;
            Tnode[i].c='a'+i;
            Tnode[i].value=num[i];
            Tnode[i].flag=1;
        }
    }
    max=len+2;
    //start
    for(i=0;i<n-1;i++){
        int min1=max+1,min2=max+1;
        int min1c,min2c;
        for(j=0;j<52;j++){
            if(Tnode[j].flag){
                if(Tnode[j].value<min1){
                    if(min1<min2){
                        min2=min1;
                        min2c=min1c;
                    }
                    min1=Tnode[j].value;
                    min1c=j;
                }
                else if(Tnode[j].value<min2){
                    min2=Tnode[j].value;
                    min2c=j;
                }
            }
        }//printf("min1:%d min2:%d min1c:%d min2c:%d\n",min1,min2,min1c,min2c);
        //for(k=0;k<10;k++){
        //    printf("value:%d flag:%d c:%c\n",Tnode[k].value,Tnode[k].flag,Tnode[k].c);   
        //}printf("\n");
        Tnode[min1c].flag=Tnode[min2c].flag=0;
        for(j=0;j<52;j++){
            if(Tnode[j].value==0){
                Tnode[j].flag=1;
                Tnode[j].left=&Tnode[min1c];
                Tnode[j].right=&Tnode[min2c];
                Tnode[min1c].parent=&Tnode[j];
                Tnode[min2c].parent=&Tnode[j];
                Tnode[j].value=Tnode[min1c].value+Tnode[min2c].value;
                break;
            }
        }
    }
    //end
   // for(i=0;i<52;i++){
   //     printf("value:%d flag:%d c:%c\n",Tnode[i].value,Tnode[i].flag,Tnode[i].c);   
   // }printf("\n");
    
    //output start 
    node *p;
    for(i=0;i<52;i++){
        if(Tnode[i].c>0){
            p=&Tnode[i];
            hafflen[Tnode[i].c-'a']=0;
            while(p->parent!=NULL){
                if(p->parent->left==p) 
                    haff[Tnode[i].c-'a'][hafflen[Tnode[i].c-'a']]='0';
                else haff[Tnode[i].c-'a'][hafflen[Tnode[i].c-'a']]='1';
                p=p->parent;
                hafflen[Tnode[i].c-'a']++;
            }haff[Tnode[i].c-'a'][hafflen[Tnode[i].c-'a']]='\0';
        }   
    }
    //output start
    for(i=0;i<26;i++){
        if(Tnode[i].c>0){
            printf("%c:",Tnode[i].c);   
            for(j=hafflen[i]-1;j>=0;j--){
                printf("%c",haff[i][j]);   
            }printf("\n");
        }
    }printf("After change:");
    for(i=0;i<len;i++){
        c=in[i];
        for(j=hafflen[c-'a']-1;j>=0;j--){
            printf("%c",haff[c-'a'][j]);   
        }   
    }printf("\n");
    //output end
    system("pause");
}
    return 0;   
}
