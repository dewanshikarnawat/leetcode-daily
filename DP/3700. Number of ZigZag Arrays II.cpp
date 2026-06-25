//Problem: 3700. Number of ZigZag Arrays II
//Topic: Dynamic Programming (DP)
//Pattern: Hard

class Solution {
public:
    static const long long MOD = 1000000007LL;
    using Matrix = vector<vector<long long>>;

    Matrix multiply(const Matrix& A, const Matrix& B) {
        int sz = A.size();
        Matrix C(sz, vector<long long>(sz, 0));

        for (int i = 0; i < sz; i++) {
            for (int k = 0; k < sz; k++) {
                if (!A[i][k]) continue;
                for (int j = 0; j < sz; j++) {
                    if (!B[k][j]) continue;
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    vector<long long> multiplyMatVec(const Matrix& A,
                                     const vector<long long>& v) {
        int sz = A.size();
        vector<long long> res(sz, 0);

        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                if (!A[i][j]) continue;
                res[i] = (res[i] + A[i][j] * v[j]) % MOD;
            }
        }
        return res;
    }

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        int states = 2 * m;

        vector<long long> base(states, 0);

        // Length = 2 states
        for (int i = 0; i < m; i++) {
            base[i] = i;               // up state
            base[m + i] = m - 1 - i;   // down state
        }

        Matrix T(states, vector<long long>(states, 0));

        // up[i] <- down[j] where j < i
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < i; j++) {
                T[i][m + j] = 1;
            }
        }

        // down[i] <- up[j] where j > i
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                T[m + i][j] = 1;
            }
        }

        long long p = n - 2;

        while (p > 0) {
            if (p & 1) base = multiplyMatVec(T, base);

            p >>= 1;
            if (p) T = multiply(T, T);
        }

        long long ans = 0;
        for (long long x : base) {
            ans = (ans + x) % MOD;
        }

        return (int)ans;
    }
};
