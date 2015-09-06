import random
class UndirectedGraphNode(object):
	def __init__(self, x):
		self.label = x
		self.neighbors = []

class Solution(object):
	def cloneGraph(self, node):
		self.dict = {}
		return self.copyNode(node, None)

	def copyNode(self, node, prev):
		r = None
		if node :
			if not self.dict.has_key(node):
				r = UndirectedGraphNode(node.label)
				self.dict[node] = r
				for x in node.neighbors:					
					self.copyNode(x, r)
			else :
				r = self.dict[node]
		if prev:
			if r:
				prev.neighbors.append(r)
		return r

list = {}
def RandomList(num):
	for x in xrange(1,num+1):
		list[x] = UndirectedGraphNode(x)
	for x in xrange(1,num+1):
		for y in xrange(1,num+1):
			if x!= y:
				r = random.randint(0,1)
				if r == 1:
					list[x].neighbors.append(list[y])

def PrintUndirectedGraphNode(node):
	dict = {}
	flag = {}
	dict[node] = 1
	flag[node] = 1
	while len(dict) != 0:
		key = dict.keys()[0]
		s = [key.label]
		for x in key.neighbors:
			s.append(x.label)
			if not flag.has_key(x):
				dict[x] = 1;
				flag[x] = 1;
		del dict[key]
		print s
		

if __name__ == '__main__':
	s = Solution()
	RandomList(10)
	PrintUndirectedGraphNode(list[1])
	PrintUndirectedGraphNode(s.cloneGraph(list[1]))

