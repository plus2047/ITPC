# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def inorderTraversal(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        stack = [(root, 0)]
        res = []
        while len(stack) > 0:
            node, pos = stack.pop()
            if node:
                if pos == 0:
                    stack.append((node, 1))
                    stack.append((node.left, 0))
                elif pos == 1:
                    res.append(node.val)
                    # stack.append((node, 2))
                    stack.append((node.right, 0))
                # elif pos == 2:
                #     pass
        
        return res
