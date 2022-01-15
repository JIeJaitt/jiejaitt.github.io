class Solution:
    def removeElement(self, nums: List[int], val: int) -> int:
        if not nums:
            return 0
        n=len(nums)
        left=0
        for right in range(0,n):
            if nums[right]!=val:
                nums[left]=nums[right]
                left+=1
        return left