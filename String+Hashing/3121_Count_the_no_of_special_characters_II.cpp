//Problem: 3121. Count the Number of Special Characters II
//Topic: String + Hashing
//Difficulty: Medium

class Solution {
public:
    int numberOfSpecialChars(string word) {
     vector<int> firstUpper(26, INT_MAX);
        vector<int> lastLower(26, -1);
        
        int n = word.size();
        
        for (int i = 0; i < n; i++) {
            char ch = word[i];
            
            if (islower(ch)) {
                lastLower[ch - 'a'] = i;
            } else {
                int idx = ch - 'A';
                firstUpper[idx] = min(firstUpper[idx], i);
            }
        }
        
        int count = 0;
        
        for (int i = 0; i < 26; i++) {
            if (lastLower[i] != -1 && firstUpper[i] != INT_MAX) {
                if (lastLower[i] < firstUpper[i]) {
                    count++;
                }
            }
        }
        
        return count;   
    }
};
