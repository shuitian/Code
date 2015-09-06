class TreeNode(object):
	def __init__(self, x):
		self.val = x
		self.left = None
		self.right = None

class Solution(object):
	def minDepth(self, root):
		if root == None:
			return 0;
		left = self.minDepth(root.left)
		right = self.minDepth(root.right)
		if left == 0:
			if right == 0:
				return 1
			else :
				return right +1
		else:
			if right == 0:
				return left +1
			else :
				if left>right:
					return right +1
				else :
					return left+1

if __name__ == '__main__':
    s = Solution()
    r1 = TreeNode(1)
    r2 = TreeNode(1)
    r3 = TreeNode(1)
    r4 = TreeNode(1)
    r5 = TreeNode(1)
    r6 = TreeNode(1)
    r7 = TreeNode(1)
    r1.left = r2;
    r1.right = r3;
    r2.left = r4;
    print s.minDepth(r1)