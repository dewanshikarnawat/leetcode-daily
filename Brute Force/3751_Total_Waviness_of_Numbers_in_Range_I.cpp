//Problem: 3751. Total Waviness of Numbers in Range I
//Topic: Brute-force digit simulation problem
//Pattern: Medium

class Solution {
public:
int getWaviness(int x) {
        string s = to_string(x);
        int n = s.size();
        
        if (n < 3) return 0;
        
        int count = 0;
        
        for (int i = 1; i < n - 1; i++) {
            int cur = s[i] - '0';
            int left = s[i - 1] - '0';
            int right = s[i + 1] - '0';
            
            if ((cur > left && cur > right) ||
                (cur < left && cur < right)) {
                count++;
            }
        }
        
        return count;
    }
    int totalWaviness(int num1, int num2) {
        int total = 0;
        
        for (int i = num1; i <= num2; i++) {
            total += getWaviness(i);
        }
        
        return total;
    }
};
