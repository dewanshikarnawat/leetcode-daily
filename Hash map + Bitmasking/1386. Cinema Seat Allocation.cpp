//Problem: 1386. Cinema Seat Allocation
//Topic: Hash map + Bitmasking
//Pattern: Medium

class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> rows;

        // Store reserved seats as a bitmask for each row.
        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int s = seat[1];

            rows[row] |= (1 << (s - 1));
        }

        // Every row with no reservations can fit 2 groups.
        long long ans = 2LL * (n - rows.size());

        // Masks for:
        // seats 2,3,4,5
        // seats 4,5,6,7
        // seats 6,7,8,9
        int left  = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4);
        int mid   = (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6);
        int right = (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8);
        for (auto &[row, mask] : rows) {
            bool canLeft = (mask & left) == 0;
            bool canMid = (mask & mid) == 0;
            bool canRight = (mask & right) == 0;

            if (canLeft && canRight) {
                // Two non-overlapping groups.
                ans += 2;
            }
            else if (canLeft || canMid || canRight) {
                // At least one block is available.
                ans += 1;
            }
        }

        return (int)ans;
    }
};
