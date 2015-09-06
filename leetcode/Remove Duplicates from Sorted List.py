class ListNode(object):

	def __init__(self, x, prev):
		self.val = x
		self.next = None
		if prev:
			prev.next = self

class Solution(object):
	def deleteDuplicates(self, head):
		t_head = head
		while head:
			first = head.val
			if head.next!=None:
				if head.next.val != first:
					first = head.next.val
					head = head.next
				else :
					head.next = head.next.next
			else :
				break
		return t_head

def PrintSortList(head):
	s = []
	while head:
		s.append(head.val)
		head = head.next
	print s

if __name__ == '__main__':
	s = Solution()
	r1 = ListNode(1, None)
	r2 = ListNode(1, r1)
	r3 = ListNode(2, r2)
	r4 = ListNode(3, r3)
	r5 = ListNode(3, r4)
	r6 = ListNode(3, r5)
	r7 = ListNode(4, r6)
	PrintSortList(r1)
	PrintSortList(s.deleteDuplicates(r1))