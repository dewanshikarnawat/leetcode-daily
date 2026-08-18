//Problem: 3471. Find the Largest Almost Missing Integer
//Topic: Hashing
//Pattern: Easy

class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        
        // count[x] = number of size-k subarrays containing x
        vector<int> count(51, 0);
        
        // Consider every subarray of size k
        for (int i = 0; i <= n - k; i++) {
            set<int> seen;
            
            for (int j = i; j < i + k; j++) {
                seen.insert(nums[j]);
            }
            
            // Count this subarray once for each distinct number
            for (int x : seen) {
                count[x]++;
            }
        }
        for (int x = 50; x >= 0; x--) {
            if (count[x] == 1) {
                return x;
            }
        }
        
        return -1;
    }
};
