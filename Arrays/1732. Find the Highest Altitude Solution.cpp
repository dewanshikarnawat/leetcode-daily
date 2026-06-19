//Problem: 1732. Find the Highest Altitude
//Topic: Array - Prefix Sum (Running Sum / Cumulative Sum)
//Pattern: Easy

class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int altitude = 0;
        int maxAltitude = 0;

        for (int g : gain) {
            altitude += g;
            maxAltitude = max(maxAltitude, altitude);
        }

        return maxAltitude;
    }
};
