//Problem: 1140. Stone Game II
//Topic: DP
//Pattern: Medium

class Solution {
public:
int n;
    vector<int> suffix;
    vector<vector<int>> dp;

    int solve(int i, int M, vector<int>& piles) {
        // All remaining piles can be taken
        if (i >= n)
            return 0;

        if (2 * M >= n - i)
            return suffix[i];

        if (dp[i][M] != -1)
            return dp[i][M];

        int best = 0;

        // Try taking X piles
        for (int X = 1; X <= 2 * M && i + X <= n; X++) {
            int opponent = solve(i + X, max(M, X), piles);

            // Total stones remaining - stones opponent can get
            int current = suffix[i] - opponent;

            best = max(best, current);
        }

        return dp[i][M] = best;
    }

    int stoneGameII(vector<int>& piles) {
         n = piles.size();

        // suffix[i] = sum of piles[i...n-1]
        suffix.resize(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        dp.assign(n, vector<int>(n + 1, -1));

        return solve(0, 1, piles);
    }
};
