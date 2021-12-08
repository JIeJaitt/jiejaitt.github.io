class Solution:
    def findRepeatNumber(self, nums: List[int]) -> int:
        nums.sort()
        pre=nums[0]
        n=len(nums)
        for idx in range(1,n):
            if pre == nums[idx]:
                return pre
            pre=nums[idx]
