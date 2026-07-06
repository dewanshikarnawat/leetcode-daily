//Problem: 1288. Remove Covered Intervals
//Topic: Sorting (Custom Comparator / Greedy)
//Pattern: Medium

class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 if (a[0] == b[0])
                     return a[1] > b[1];   // larger end first
                 return a[0] < b[0];
             });

        int count = 0;
        int maxEnd = -1;

        for (auto &interval : intervals) {
            if (interval[1] > maxEnd) {
                count++;
                maxEnd = interval[1];
            }
        }

        return count;
    }
};
