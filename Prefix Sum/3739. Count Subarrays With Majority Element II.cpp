//Problem: 3739. Count Subarrays With Majority Element II
//Topic: Prefix Sum + Fenwick Tree (Binary Indexed Tree) + Binary Search / Coordinate Compression + Array Transformation
//Pattern: Hard

class Solution {
public:
    struct BIT {
        int n;
        vector<int> bit;
        BIT(int sz) {
            n = sz;
            bit.assign(n + 1, 0);
        }
        void add(int idx, int val) {
            while (idx <= n) {
                bit[idx] += val;
                idx += idx & -idx;
            }
        }
        int query(int idx) {
            int res = 0;
            while (idx > 0) {
                res += bit[idx];
                idx -= idx & -idx;
            }
            return res;
        }
    };
    
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();

        int offset = n + 1;
        int size = 2 * n + 5;

        BIT ft(size);

        long long ans = 0;
        int pref = 0;

        ft.add(offset, 1);

        for (int x : nums) {
            pref += (x == target ? 1 : -1);

            int idx = pref + offset;

            ans += ft.query(idx - 1);

            ft.add(idx, 1);
        }

        return ans;
    }
};
