#include <iostream>
#include <string>
using namespace std;
class Solution {
public:
    string addBinary(string a, string b) {
        int len1 = a.length();
        int len2 = b.length();
        int max = (len1>len2?len1:len2)+2;
        char c[max];
        c[0] = '0' ;
        c[max-1] = 0 ;
        int i = a.length()-1;
        int j = b.length()-1;
        int k = max-2;
        int overflow = 0;
        for(;i>=0 && j>=0; i--,j--){
            c[k] = a[i] - '0' +b[j]  + overflow;
            if(c[k] >= '2'){
                overflow = 1;
                c[k] = c[k]-2;
            }else {
                overflow = 0;
            }
            k--;
        }
        if(i>=0){
            for(;i>=0; i--){

                c[k] = a[i] + overflow;
                if(c[k] >= '2'){
                    overflow = 1;
                    c[k] = c[k]-2;
                }else {
                    overflow = 0;
                }
                k--;
            }
        }else if(j>=0){
            for(;j>=0; j--){

                c[k] = b[j] + overflow;
                if(c[k] >= '2'){
                    overflow = 1;
                    c[k] = c[k]-2;
                }else {
                    overflow = 0;
                }
                k--;
            }  
        }
        c[k] = '0'+overflow;
        if(len1 == 1 && a[0] == '0' && len2 == 1 && b[0] == '0'){
            return "0";
        }else if(c[k] == '0'){
            return string(c+1)   ;
        }else {
            return string(c)   ;
        }
    }
};
int main(){
    Solution s;
    cout<<s.addBinary("0","1")<<endl;
    system("pause");
    return 0;   
}
