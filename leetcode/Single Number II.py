class Solution(object):
	def singleNumber(self, nums):
		dict = {}
		for x in nums:
			if dict.has_key(x):
				dict[x] = dict[x] + 1
				if dict[x] == 3:
					del dict[x]
			else :
				dict[x] = 1
		return dict.keys()[0]

if __name__ == '__main__':
 	s = Solution()
 	nums = [1,1,1,2,2,3,4,3,3,5,5,4]
 	print s.singleNumber(nums) 