//Problem: 3614. Process String with Special Operations II
//Topic: String, Simulation, Stack
//Pattern: Hard

class Solution {
public:
    char processStr(string s, long long k) {
       int n = s.size();
        vector<long long> len(n + 1, 0);

        // Pass 1: compute lengths
        for (int i = 0; i < n; i++) {
            len[i + 1] = len[i];

            if (islower(s[i])) {
                len[i + 1]++;
            } 
            else if (s[i] == '*') {
                if (len[i + 1] > 0) len[i + 1]--;
            } 
            else if (s[i] == '#') {
                len[i + 1] *= 2;
            }
            // '%' -> length unchanged
        }

        if (k >= len[n]) return '.';

        // Pass 2: work backwards
        for (int i = n - 1; i >= 0; i--) {
            char c = s[i];

            if (islower(c)) {
                if (k == len[i])
                    return c;
            }
            else if (c == '*') {
                // nothing to do
            }
            else if (c == '#') {
                if (len[i] > 0)
                    k %= len[i];
            }
            else if (c == '%') {
                if (len[i] > 0)
                    k = len[i] - 1 - k;
            }
        }

        return '.'; 
    }
};
