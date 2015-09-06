import random
class RandomListNode(object):
	def __init__(self, x):
		self.label = x
		self.next = None
		self.random = None

class Solution(object):
	def copyRandomList(self, head):
		self.dict = {}
		return self.copyNode(head, None, True)

	def copyNode(self, node, prev, flag):
		r = None
		if node :
			if not self.dict.has_key(node):
				r = RandomListNode(node.label)
				self.dict[node] = r
				self.copyNode(node.next, r , True)
				self.copyNode(node.random, r , False)
			else :
				r = self.dict[node]
		if prev:
			if flag:
				prev.next = r
			else :
				prev.random = r
		return r


list = {}
def RandomList(num):
	for x in xrange(1,num+1):
		list[x] = RandomListNode(x)
	for x in xrange(1,num):
		list[x].next = list[x+1]
	for x in xrange(1,num+1):
		list[x].random = list[random.randint(1,num)]

def PrintRandomListNode(node):
	while node:
		if node.random:
			print node.label,node.random.label
		else :
			print node.label,None
		node = node.next

if __name__ == '__main__':
	s = Solution()
	RandomList(10)
	PrintRandomListNode(list[1])
	PrintRandomListNode(s.copyRandomList(list[1]))

