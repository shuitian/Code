# The isBadVersion API is already defined for you.
# @param version, an integer
# @return a bool
def isBadVersion(version):
	if version<1111:
		return False
	else :
		return True

class Solution(object):
	def firstBadVersion(self, n):
		return self.binaryChop(1, n)

	def binaryChop(self, begin, end):
		if begin == end :
			return begin
		half = (begin+end)/2
		if isBadVersion(half):
			return self.binaryChop(begin, half)
		else :
			return self.binaryChop(half+1, end)


if __name__ == '__main__':
	s = Solution()
	print s.firstBadVersion(100)
