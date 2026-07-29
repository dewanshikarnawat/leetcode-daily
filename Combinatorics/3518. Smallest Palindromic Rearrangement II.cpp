//Problem: 3518. Smallest Palindromic Rearrangement II
//Topic: Combinatorics
//Pattern: Hard

class Solution {
public:
static const int LIMIT = 1000001;
    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char c : s) freq[c - 'a']++;

        string mid = "";
        vector<int> cnt(26);

        for (int i = 0; i < 26; i++) {
            cnt[i] = freq[i] / 2;
            if (freq[i] % 2)
                mid.push_back(char('a' + i));
        }

        int m = s.size() / 2;

        // Pascal combinations capped at LIMIT
        vector<vector<int>> C(m + 1);
        for (int i = 0; i <= m; i++) {
            C[i].resize(i + 1);
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < i; j++) {
                long long v = 1LL * C[i - 1][j - 1] + C[i - 1][j];
                if (v > LIMIT) v = LIMIT;
                C[i][j] = (int)v;
            }
        }

        auto countWays = [&](vector<int>& f) {
            long long ans = 1;
            int rem = 0;
            for (int x : f) rem += x;

            int left = rem;
            for (int x : f) {
                if (x == 0) continue;
                ans *= C[left][x];
                if (ans >= LIMIT) return LIMIT;
                left -= x;
            }
            return (int)ans;
        };

        if (countWays(cnt) < k) return "";

        string half = "";

        for (int pos = 0; pos < m; pos++) {
            for (int c = 0; c < 26; c++) {
                if (cnt[c] == 0) continue;

                cnt[c]--;
                int ways = countWays(cnt);

                if (ways >= k) {
                    half.push_back(char('a' + c));
                    break;
                } else {
                    k -= ways;
                    cnt[c]++;
                }
            }
        }

        string rev = half;
        reverse(rev.begin(), rev.end());
        return half + mid + rev;
    }
};
