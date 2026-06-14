//Problem: 3838. Weighted Word Mapping
//Topic: Array + String
//Pattern: Easy

class Solution {
public:
    string mapWordWeights(vector<string>& words, vector<int>& weights) {
        string result;
        
        for (string &word : words) {
            int sum = 0;
            
            for (char ch : word) {
                sum += weights[ch - 'a'];
            }
            
            int mod = sum % 26;
            
            // Reverse alphabetical mapping:
            // 0 -> 'z', 1 -> 'y', ..., 25 -> 'a'
            result.push_back('z' - mod);
        }
        
        return result;
    }
};
