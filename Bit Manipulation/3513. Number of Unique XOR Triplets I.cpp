//Problem: 3513. Number of Unique XOR Triplets I
//Topic: Bit Manipulation
//Pattern: Medium

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();

        if (n < 3) return n;

        int ans = 1;
        while (ans <= n) ans <<= 1;

        return ans;
    }
};
