class Solution {
    public int[] twoSum(int[] nums, int target) {
        for(int i=0;i<nums.length;i++)
            for(int j=0;j<i;j++)
                if(nums[j] == target - nums[i])
                                  return new int[] {j,i};
        return null;
    }
}
