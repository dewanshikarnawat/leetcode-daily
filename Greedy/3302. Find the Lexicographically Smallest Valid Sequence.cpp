//Problem: 3302. Find the Lexicographically Smallest Valid Sequence
//Topic: Greedy + String Matching / Subsequence + Suffix Preprocessing
//Pattern: Medium

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<int> suf(n + 1, m);

        // suf[i] = first index of word2 that cannot be
        // matched using word1[i...n-1] exactly.
        int j = m - 1;

        for (int i = n - 1; i >= 0; i--) {
            if (j >= 0 && word1[i] == word2[j]) {
                j--;
            }

            suf[i] = j + 1;
        }

        vector<int> ans;

        j = 0;
        bool usedMismatch = false;

        for (int i = 0; i < n && j < m; i++) {

            // Normal matching character
            if (word1[i] == word2[j]) {
                ans.push_back(i);
                j++;
            }

            // Use our one allowed mismatch
            else if (!usedMismatch && suf[i + 1] <= j + 1) {
                ans.push_back(i);
                j++;
                usedMismatch = true;
            }
        }

        if (j == m)
            return ans;

        return {};
    }
};
