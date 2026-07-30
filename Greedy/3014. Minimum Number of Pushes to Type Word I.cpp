//Problem: 3014. Minimum Number of Pushes to Type Word I
//Topic: Greedy
//Pattern: Easy

class Solution {
public:
    int minimumPushes(string word) {
        int n = word.size();
        int ans = 0;

        for (int i = 0; i < n; i++) {
            ans += (i / 8) + 1;
        }

        return ans;
    }
};
