#include <stdio.h>
class Solution {
public:
    bool isUgly(int num) {
        while(!(num&1) && num>1){
        	num>>=1;
        }
        while(num%3 == 0 && num>1){
        	num/=3;
        }
        while(num%5 == 0 && num>1){
        	num/=5;
        }
        if(num == 1){
        	return true;
        }else {
        	return false;
        }
    }
};

int main(int argc, char const *argv[])
{
	Solution solution;
	for (int i = 1; i < 1000; ++i)
	{
		printf("%d: %s\n",i,(solution.isUgly(i)?"true!":"false!"));
	}
	return 0;
}
