class Solution(object):
	def isHappy(self, n):
		dict = {}
		while not dict.has_key(n):
			dict[n] = 1
			k = n
			s = 0
			while k>0:
				p = k%10
				s = s+ p*p
				k = k/10
			n = s
		if n == 1:
			return True
		else:
			return False

if __name__ == '__main__':
    s = Solution()
    print s.isHappy(82)