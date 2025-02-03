# You are given an array nums of length n. You are also given an integer k.
# You perform the following operation on nums once:
# Select a subarray nums[i..j] where 0 <= i <= j <= n - 1.
# Select an integer x and add x to all the elements in nums[i..j].
# Find the maximum frequency of the value k after the operation.

# 1 <= n == nums.length <= 10^5
# 1 <= nums[i] <= 50
# 1 <= k <= 50

from typing import List

class Solution:
    def maxFrequency(self, nums: List[int], k: int) -> int:
        n = len(nums)
        
        prefix_k_count = [int(nums[i] == k) for i in range(n)]
        for i in range(1, n):
            prefix_k_count[i] += prefix_k_count[i-1]
        
        res = 0
        for target in set(nums):
            prefix_target_count = [int(nums[i] == target) for i in range(n)]
            for i in range(1, n):
                prefix_target_count[i] += prefix_target_count[i-1]
            
            prefix_diff = [prefix_target_count[i] - prefix_k_count[i] for i in range(n)]
            
            stack = []
            for i in range(n - 1, -1, -1):
                if not stack or prefix_diff[i] >= prefix_diff[stack[-1]]:
                    stack.append(i)

            for i in range(n):
                while stack and stack[-1] < i:
                    stack.pop()
                if stack:
                    curr = prefix_k_count[-1] + prefix_diff[stack[-1]] - (prefix_diff[i - 1] if i > 0 else 0)
                    res = max(res, curr)
        
        return res


def test_solution():
    s = Solution()
    assert s.maxFrequency([5,1,9,7,1,5], 1) == 3
    assert s.maxFrequency([10,2,3,4,5,5,4,3,2,2], 10) == 4
    assert s.maxFrequency([1,2,3,4,5], 1) == 2
    assert s.maxFrequency([1,1,1,1,1], 2) == 5

if __name__ == "__main__":
    test_solution()
