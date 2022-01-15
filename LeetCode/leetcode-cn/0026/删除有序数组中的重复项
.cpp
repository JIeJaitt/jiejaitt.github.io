// 双指针
  // （1）
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n=nums.size();
        if(n==0) return 0;

        int fast=1,slow=1;
        while(fast<n) {
            if(nums[fast]!=nums[fast-1]) {
                nums[slow]=nums[fast];
                ++slow;
            }
            ++fast;
        } 
        return slow;
    }
};

  // （2）
class Solution {
    public int removeDuplicates(int[] nums) {
        // 未重复数组索引
        int pos = 0; 
        for (int i = 0; i < nums.length; i++) {
            // 去重
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            nums[pos] = nums[i];
            pos++;
        }
        return pos;
    }
}