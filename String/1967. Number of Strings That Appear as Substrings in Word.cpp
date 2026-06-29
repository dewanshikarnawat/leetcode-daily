//Problem: 1967. Number of Strings That Appear as Substrings in Word
//Topic: Strings – Substring Search
//Pattern: Easy

class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
        int count = 0;

        for (string &pattern : patterns) {
            if (word.find(pattern) != string::npos) {
                count++;
            }
        }

        return count;
    }
};
