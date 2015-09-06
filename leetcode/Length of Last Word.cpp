#include <iostream>
#include <string>
using namespace std;
class Solution {
public:
    int lengthOfLastWord(string s) {
        int result = 0;
        bool flag = false;
        if(s.length() == 0){
            return 0;   
        }
        for(int i = s.length() - 1; i>=0; i--){
            if(s[i]!=' '){
                result++;   
                flag = true;
            }else if(flag){
                break;
            }
        }
        return result;
    }
};
int main(){
    Solution s;
    cout<<s.lengthOfLastWord("a123")<<endl;
    system("pause");
    return 0;   
}
