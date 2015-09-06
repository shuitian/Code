class Solution(object):
	def missingNumber(self, nums):
		dict = {}
		for x in nums:
			dict[x] = 1
		for x in xrange(0,len(nums)+1):
			if not dict.has_key(x):
				return x

				

if __name__ == '__main__':
	s = Solution()
	nums = [1,2,4,6,3,7]
	print s.missingNumber(nums)