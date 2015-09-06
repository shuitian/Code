class Solution(object):
	def findPeakElement(self, nums):
		for x in xrange(0,len(nums)-1):
			if(nums[x]>nums[x+1]):
				return x
		return len(nums)-1

if __name__ == '__main__':
	s = Solution()
	nums = [1,2,3]
	print s.findPeakElement(nums)