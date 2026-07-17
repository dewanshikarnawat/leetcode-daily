//Problem: 3312. Sorted GCD Pair Queries
//Topic: Number Theory
//Pattern: Hard

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<int> freq(mx + 1, 0);
        for (int x : nums) freq[x]++;

        // cnt[g] = numbers divisible by g
        vector<long long> cnt(mx + 1, 0);
        for (int g = 1; g <= mx; g++) {
            for (int m = g; m <= mx; m += g)
                cnt[g] += freq[m];
        }

        // exact[g] = pairs having gcd exactly g
        vector<long long> exact(mx + 1, 0);

        for (int g = mx; g >= 1; g--) {
            exact[g] = cnt[g] * (cnt[g] - 1) / 2;
            for (int m = 2 * g; m <= mx; m += g)
                exact[g] -= exact[m];
        }

        // prefix counts
        vector<long long> prefix(mx + 1, 0);
        for (int g = 1; g <= mx; g++)
            prefix[g] = prefix[g - 1] + exact[g];

        vector<int> ans;
        ans.reserve(queries.size());

        for (long long q : queries) {
            int g = lower_bound(prefix.begin() + 1, prefix.end(), q + 1) - prefix.begin();
            ans.push_back(g);
        }

        return ans;
    }
};
