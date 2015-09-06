#include<iostream> 
using namespace std;

char * ToHexBin(char * input){
    char *result;
    unsigned int nOutSize=strlen(input);  
    unsigned int i,test;
    result = (char *)malloc(nOutSize*4+1);
    for (i=0;i<nOutSize;i++){
        switch(input[i])
        {
        case 'F':
        case 'f':
            test=15;
            break;
        case 'E':
        case 'e':
            test=14;
            break;
        case 'D':
        case 'd':
            test=13;
            break;
        case 'C':
        case 'c':
            test=12;
            break;
        case 'B':
        case 'b':
            test=11;
            break;
        case 'A':
        case 'a':
            test=10;
            break;
        default :
            test=input[i]-'0';
        }  
        result[i*4+3]='0'+(test&1);
        result[i*4+2]='0'+(test>>1&1);
        result[i*4+1]='0'+(test>>2&1);
        result[i*4]='0'+(test>>3&1);
    }result[i*4]=0;
    return result;
}

unsigned int ToBinLowDec(char * input){
    unsigned int output=0;
    for (int i=0;i<strlen(input);i++){
        output=output*2+input[i]-'0';
    }return output;
}
int main(){
    char in[30];
while(1){
    gets(in);
    //printf("%d %d\n",sizeof(in),strlen(in));
    puts(ToHexBin(in));
    printf("%d\n",ToBinLowDec(ToHexBin(in)));
    system("pause");
}
    return 0;   
}
