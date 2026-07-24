//Problem: 3514. Number of Unique XOR Triplets II
//Topic: Bit Manipulation
//Pattern: Medium

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<bool> present(MAXX, false);
        vector<int> values;

        for (int x : nums) {
            if (!present[x]) {
                present[x] = true;
                values.push_back(x);
            }
        }

        vector<vector<bool>> dp(4, vector<bool>(MAXX, false));
        dp[0][0] = true;

        for (int t = 1; t <= 3; t++) {
            for (int x = 0; x < MAXX; x++) {
                if (!dp[t - 1][x]) continue;
                for (int v : values) {
                    dp[t][x ^ v] = true;
                }
            }
        }

        int ans = 0;
        for (bool ok : dp[3]) {
            if (ok) ans++;
        }

        return ans;
    }
};
