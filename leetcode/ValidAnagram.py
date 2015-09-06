class Solution(object):
	def isAnagram(self, s, t):
		dic = {}
		for x in ''.join(s):
			if x in dic:
				dic[x] = dic[x]+1;
			else :
				dic[x]=1;
		for x in ''.join(t):
			if x in dic:
				dic[x] = dic[x]-1;
				if dic[x] == -1:
					return False;
				if dic[x] == 0:
					del dic[x]
			else :
				return False
		if len(dic) == 0:
			return True;
		return False;


if __name__ == '__main__':
	s = Solution();
	print s.isAnagram("cat","ca");