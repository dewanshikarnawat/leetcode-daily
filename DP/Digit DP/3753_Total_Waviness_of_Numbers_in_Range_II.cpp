//Problem: 3753. Total Waviness of Numbers in Range II
//Topic: Dynamic Programming (Digit DP)
//Pattern: Hard

class Solution {
public:
    struct Node {
        long long cnt = 0;
        long long sum = 0;
        bool vis = false;
    };

    string s;
    Node dp[20][3][11][11];

    pair<long long, long long> dfs(int pos, bool tight, int lenState,
                                   int prev2, int prev1) {
        if (pos == (int)s.size()) {
            return {1, 0}; // one valid number, no more contributions
        }

        if (!tight && dp[pos][lenState][prev2][prev1].vis) {
            return {
                dp[pos][lenState][prev2][prev1].cnt,
                dp[pos][lenState][prev2][prev1].sum
            };
        }

        long long totalCnt = 0;
        long long totalSum = 0;

        int limit = tight ? (s[pos] - '0') : 9;

        for (int d = 0; d <= limit; d++) {
            bool ntight = tight && (d == limit);

            if (lenState == 0) {
                if (d == 0) {
                    auto [cnt, sum] = dfs(pos + 1, ntight, 0, 10, 10);
                    totalCnt += cnt;
                    totalSum += sum;
                } else {
                    auto [cnt, sum] = dfs(pos + 1, ntight, 1, 10, d);
                    totalCnt += cnt;
                    totalSum += sum;
                }
            }
            else if (lenState == 1) {
                auto [cnt, sum] = dfs(pos + 1, ntight, 2, prev1, d);
                totalCnt += cnt;
                totalSum += sum;
            }
            else { // lenState == 2, we already have two previous digits
                int contrib = 0;

                if (prev1 > prev2 && prev1 > d) contrib = 1; // peak
                else if (prev1 < prev2 && prev1 < d) contrib = 1; // valley

                auto [cnt, sum] = dfs(pos + 1, ntight, 2, prev1, d);

                totalCnt += cnt;
                totalSum += sum + 1LL * contrib * cnt;
            }
        }

        if (!tight) {
            dp[pos][lenState][prev2][prev1].vis = true;
            dp[pos][lenState][prev2][prev1].cnt = totalCnt;
            dp[pos][lenState][prev2][prev1].sum = totalSum;
        }

        return {totalCnt, totalSum};
    }

    long long solve(long long N) {
        if (N < 0) return 0;

        s = to_string(N);

        for (int i = 0; i < 20; i++)
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 11; k++)
                    for (int l = 0; l < 11; l++)
                        dp[i][j][k][l] = Node();

        return dfs(0, true, 0, 10, 10).second;
    }
    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};
