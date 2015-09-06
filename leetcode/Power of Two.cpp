#include <stdio.h>
class Solution {
public:
    bool isPowerOfTwo(int n) {
        while(n>1){
        	if(n&1){
        		return false;
        	}
        	n>>=1;
        }
        if(n == 1)
	        return true;
	    return false;
    }
};
int main(int argc, char const *argv[])
{
	Solution *s = new Solution();
	if(s->isPowerOfTwo(128)){
		printf("1");
	}
	return 0;
}