//Problem: 3020. Find the Maximum Number of Elements in Subset
//Topic: Greedy + hashing + Math
//Pattern: Medium

class Solution {
public:
     int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> cnt;
        for (int x : nums) cnt[x]++;

        int ans = 1;

        // Handle 1 separately
        if (cnt.count(1)) {
            ans = max(ans, cnt[1] % 2 ? cnt[1] : cnt[1] - 1);
        }

        for (auto &[x, f] : cnt) {
            if (x == 1) continue;

            long long cur = x;
            int len = 1;   // current value as center

            while (cnt[cur] >= 2) {
                if (cur > 1000000000LL / cur) break;

                long long nxt = cur * cur;

                if (!cnt.count(nxt)) break;

                len += 2;
                cur = nxt;
            }

            ans = max(ans, len);
        }

        return ans;
    }
};
