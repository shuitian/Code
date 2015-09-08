class Solution(object):
	def numDecodings(self, s):

		length = len(s)
		numbers = [1, 1]
		if length == 0 or s[0] == '0':
			numbers = [0, 0]
			return 0

		for x in xrange(2,length+1):
			t = 0
			sum = int(s[x-2:x])
			if sum >9 and sum <27:
				t = t + numbers[x-2]
			sum = int(s[x-1])
			if sum >0 :
				t = t + numbers[x-1]
			numbers.append(t)
			#print numbers
		return numbers[length]



if __name__ == '__main__':
	s = Solution()
	print s.numDecodings("01")