//Problem: 3612. Process String with Special Operations I
//Topic: Simulation (String Manipulation)
//Pattern: Medium

class Solution {
public:
    string processStr(string s) {
        string result = "";
        
        for (char c : s) {
            if (c >= 'a' && c <= 'z') {
                result.push_back(c);
            }
            else if (c == '*') {
                if (!result.empty()) {
                    result.pop_back();
                }
            }
            else if (c == '#') {
                result += result;
            }
            else if (c == '%') {
                reverse(result.begin(), result.end());
            }
        }
        
        return result;
    }
};
