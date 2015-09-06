class Solution(object):
	def addDigits(self, num):
	    if num == 0:
	        return 0;
	    else:
			return (num-1)%9+1;

if __name__ == '__main__':
	s = Solution();
	print s.addDigits(1);