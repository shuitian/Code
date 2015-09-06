class TreeNode(object):
	def __init__(self, x):
		self.val = x
		self.left = None
		self.right = None

class Solution(object):
	def invertTree(self, root):
		if root:
			self.invertTree(root.left)
			self.invertTree(root.right)
			t = root.right
			root.right = root.left
			root.left = t
		return root

def PrintTree(root):
	s = [root]
	while len(s)!= 0:
		print s[0].val
		if s[0].left:
			s.append(s[0].left)
		if s[0].right:
			s.append(s[0].right)
		del s[0]

if __name__ == '__main__':
	s = Solution()
	root = TreeNode(0)
	root1 = TreeNode(1)
	root2 = TreeNode(2)
	root3 = TreeNode(3)
	root4 = TreeNode(4)
	root5 = TreeNode(5)
	root6 = TreeNode(6)
	root7 = TreeNode(7)
	root1.left = root2
	root1.right = root3
	root2.left = root4
	root2.right = root5
	root3.left = root6
	root3.right = root7
	PrintTree(root1)
	PrintTree(s.invertTree(root1))