//Problem: 3348. Smallest Divisible Digit Product II
//Topic: Brute Force
//Pattern: Hard

class Solution {
public:
    string smallestNumber(string num, long long t) {

        const int primes[4] = {2, 3, 5, 7};

        int need[4] = {0, 0, 0, 0};

        // Factorize t
        for (int i = 0; i < 4; ++i) {
            while (t % primes[i] == 0) {
                ++need[i];
                t /= primes[i];
            }
        }

        // Impossible if t has another prime factor
        if (t != 1)
            return "-1";

        // Prime factor contribution of digits 1..9
        int f[10][4] = {};

        for (int digit = 2; digit <= 9; ++digit) {

            int x = digit;

            for (int p = 0; p < 4; ++p) {

                while (x % primes[p] == 0) {
                    ++f[digit][p];
                    x /= primes[p];
                }
            }
        }

        /*
            dp[state] =
            minimum number of digits needed to satisfy
            the required prime factors.
        */

        int A = need[0] + 1;
        int B = need[1] + 1;
        int C = need[2] + 1;
        int D = need[3] + 1;

        int total = A * B * C * D;

        auto ID = [&](int a, int b, int c, int d) {
            return (((a * B) + b) * C + c) * D + d;
        };

        const unsigned char INF = 100;

        vector<unsigned char> dp(total, INF);

        dp[ID(0, 0, 0, 0)] = 0;

        /*
            Fill DP.
        */
        for (int a = 0; a <= need[0]; ++a) {
            for (int b = 0; b <= need[1]; ++b) {
                for (int c = 0; c <= need[2]; ++c) {
                    for (int d = 0; d <= need[3]; ++d) {

                        if (a == 0 && b == 0 &&
                            c == 0 && d == 0)
                            continue;

                        unsigned char best = INF;

                        for (int digit = 2; digit <= 9; ++digit) {

                            int na =
                                max(0, a - f[digit][0]);

                            int nb =
                                max(0, b - f[digit][1]);

                            int nc =
                                max(0, c - f[digit][2]);

                            int nd =
                                max(0, d - f[digit][3]);

                            unsigned char prev =
                                dp[ID(na, nb, nc, nd)];

                            if (prev != INF) {
                                best = min(
                                    best,
                                    (unsigned char)(prev + 1)
                                );
                            }
                        }

                        dp[ID(a, b, c, d)] = best;
                    }
                }
            }
        }

        int minDigits =
            dp[ID(
                need[0],
                need[1],
                need[2],
                need[3]
            )];

        if (minDigits == INF)
            return "-1";

        int n = (int)num.size();

        /*
            prefix[i] = factor counts in num[0..i-1].
        */
        vector<array<int, 4>> prefix(n + 1);

        prefix[0] = {0, 0, 0, 0};

        for (int i = 0; i < n; ++i) {

            prefix[i + 1] = prefix[i];

            int digit = num[i] - '0';

            if (digit != 0) {

                for (int p = 0; p < 4; ++p) {

                    prefix[i + 1][p] =
                        min(
                            need[p],
                            prefix[i + 1][p] +
                            f[digit][p]
                        );
                }
            }
        }

        /*
            Check if num itself is valid.
        */
        bool zeroFree = true;

        for (char c : num) {

            if (c == '0') {
                zeroFree = false;
                break;
            }
        }

        if (zeroFree) {

            bool good = true;

            for (int p = 0; p < 4; ++p) {

                if (prefix[n][p] < need[p]) {
                    good = false;
                    break;
                }
            }

            if (good)
                return num;
        }

        /*
            FIRST zero is what matters.

            If firstZero < i, then prefix [0..i-1]
            already contains zero and cannot be kept.
        */
        int firstZero = -1;

        for (int i = 0; i < n; ++i) {

            if (num[i] == '0') {
                firstZero = i;
                break;
            }
        }

        /*
            Build smallest suffix of exactly len digits.
        */
        auto buildSuffix =
            [&](int len, array<int, 4> req) {

            string res;
            res.reserve(len);

            for (int pos = 0; pos < len; ++pos) {

                int remaining = len - pos - 1;

                for (int digit = 1; digit <= 9; ++digit) {

                    int a =
                        max(
                            0,
                            req[0] - f[digit][0]
                        );

                    int b =
                        max(
                            0,
                            req[1] - f[digit][1]
                        );

                    int c =
                        max(
                            0,
                            req[2] - f[digit][2]
                        );

                    int d =
                        max(
                            0,
                            req[3] - f[digit][3]
                        );

                    if (dp[ID(a, b, c, d)] <= remaining) {

                        res.push_back(
                            char('0' + digit)
                        );

                        req[0] = a;
                        req[1] = b;
                        req[2] = c;
                        req[3] = d;

                        break;
                    }
                }
            }

            return res;
        };

        /*
            Try same-length answer.

            We change one digit to a larger digit.
        */
        for (int i = n - 1; i >= 0; --i) {

            /*
                If first zero occurs before i,
                prefix contains zero -> invalid.

                If first zero == i, it is okay because
                we are replacing that zero.
            */
            if (firstZero != -1 && firstZero < i)
                continue;

            int original = num[i] - '0';

            for (int digit = original + 1;
                 digit <= 9;
                 ++digit) {

                array<int, 4> req;

                for (int p = 0; p < 4; ++p) {

                    int have =
                        prefix[i][p] +
                        f[digit][p];

                    req[p] =
                        max(
                            0,
                            need[p] - have
                        );
                }

                int suffixLen = n - i - 1;

                if (dp[ID(
                        req[0],
                        req[1],
                        req[2],
                        req[3]
                    )] <= suffixLen) {

                    string ans =
                        num.substr(0, i);

                    ans.push_back(
                        char('0' + digit)
                    );

                    ans += buildSuffix(
                        suffixLen,
                        req
                    );

                    return ans;
                }
            }
        }

        /*
            No valid answer of same length.

            Construct smallest longer number.
        */
        int len =
            max(n + 1, minDigits);

        array<int, 4> req = {
            need[0],
            need[1],
            need[2],
            need[3]
        };

        string ans;
        ans.reserve(len);

        /*
            First digit cannot be zero.
        */
        for (int digit = 1; digit <= 9; ++digit) {

            int a =
                max(
                    0,
                    req[0] - f[digit][0]
                );

            int b =
                max(
                    0,
                    req[1] - f[digit][1]
                );

            int c =
                max(
                    0,
                    req[2] - f[digit][2]
                );

            int d =
                max(
                    0,
                    req[3] - f[digit][3]
                );

            if (dp[ID(a, b, c, d)] <= len - 1) {

                ans.push_back(
                    char('0' + digit)
                );

                req = {a, b, c, d};

                break;
            }
        }

        ans += buildSuffix(len - 1, req);

        return ans;
    }
};
