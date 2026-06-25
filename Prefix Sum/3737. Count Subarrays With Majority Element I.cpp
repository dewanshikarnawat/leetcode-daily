//Problem: 3737. Count Subarrays With Majority Element I
//Topic: Prefix Sum + Fenwick Tree (BIT) / Ordered Statistics
//Pattern: Medium

class Solution {
public:
class BIT {
    public:
        vector<int> bit;
        int n;

        BIT(int n) {
            this->n = n;
            bit.assign(n + 1, 0);
        }

        void add(int idx, int val) {
            for (; idx <= n; idx += idx & -idx)
                bit[idx] += val;
        }

        int sum(int idx) {
            int res = 0;
            for (; idx > 0; idx -= idx & -idx)
                res += bit[idx];
            return res;
        }
    };
    int countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();

        vector<int> pref(n + 1, 0);

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + (nums[i] == target ? 1 : -1);
        }

        vector<int> vals = pref;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        BIT bit(vals.size());

        long long ans = 0;

        for (int x : pref) {
            int pos = lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;

            ans += bit.sum(pos - 1); // count previous prefix sums < x

            bit.add(pos, 1);
        }

        return (int)ans;
    }
};
