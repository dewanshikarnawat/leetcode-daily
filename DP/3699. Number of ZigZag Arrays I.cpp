//Problem: 3699. Number of ZigZag Arrays I
//Topic: Dynamic Programming (DP), Prefix Sum, State Transition DP
//Pattern: Hard

class Solution {
public:
    static const int MOD = 1000000007;
    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        vector<long long> up(m, 0), down(m, 0);

        // Length = 2 initialization
        for (int v = 0; v < m; v++) {
            up[v] = v;               // choose any smaller value
            down[v] = m - 1 - v;     // choose any larger value
        }

        // Build lengths 3...n
        for (int len = 3; len <= n; len++) {
            vector<long long> newUp(m, 0), newDown(m, 0);

            // Prefix sums of down
            long long pref = 0;
            for (int v = 0; v < m; v++) {
                newUp[v] = pref;
                pref = (pref + down[v]) % MOD;
            }

            // Suffix sums of up
            long long suff = 0;
            for (int v = m - 1; v >= 0; v--) {
                newDown[v] = suff;
                suff = (suff + up[v]) % MOD;
            }

            up.swap(newUp);
            down.swap(newDown);
        }

        long long ans = 0;
        for (int v = 0; v < m; v++) {
            ans = (ans + up[v] + down[v]) % MOD;
        }

        return (int)ans;
    }
};
