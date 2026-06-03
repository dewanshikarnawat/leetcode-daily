//Problem: 3635. Earliest Finish Time for Land and Water Rides II
//Topic: Array + Binary Search + Sorting
//Pattern: Medium

class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        auto solveDirection = [&](vector<int>& start, vector<int>& dur,
                                  const vector<int>& queries) -> long long {
            int n = start.size();

            vector<pair<int, int>> rides;
            rides.reserve(n);

            for (int i = 0; i < n; i++) {
                rides.push_back({start[i], dur[i]});
            }

            sort(rides.begin(), rides.end());

            vector<int> starts(n);
            vector<long long> prefMinDur(n);
            vector<long long> suffMinStartPlusDur(n);

            for (int i = 0; i < n; i++) {
                starts[i] = rides[i].first;
            }

            for (int i = 0; i < n; i++) {
                if (i == 0)
                    prefMinDur[i] = rides[i].second;
                else
                    prefMinDur[i] = min(prefMinDur[i - 1],
                                        (long long)rides[i].second);
            }

            for (int i = n - 1; i >= 0; i--) {
                long long val = (long long)rides[i].first + rides[i].second;
                if (i == n - 1)
                    suffMinStartPlusDur[i] = val;
                else
                    suffMinStartPlusDur[i] =
                        min(suffMinStartPlusDur[i + 1], val);
            }

            long long best = LLONG_MAX;

            for (int x : queries) {
                int idx = lower_bound(starts.begin(), starts.end(), x) - starts.begin();

                long long cur = LLONG_MAX;

                if (idx < n) {
                    cur = min(cur, suffMinStartPlusDur[idx]);
                }

                if (idx > 0) {
                    cur = min(cur, (long long)x + prefMinDur[idx - 1]);
                }

                best = min(best, cur);
            }

            return best;
        };

        vector<int> landFinish(landStartTime.size());
        for (int i = 0; i < (int)landStartTime.size(); i++) {
            landFinish[i] = landStartTime[i] + landDuration[i];
        }

        vector<int> waterFinish(waterStartTime.size());
        for (int i = 0; i < (int)waterStartTime.size(); i++) {
            waterFinish[i] = waterStartTime[i] + waterDuration[i];
        }

        long long landThenWater =
            solveDirection(waterStartTime, waterDuration, landFinish);

        long long waterThenLand =
            solveDirection(landStartTime, landDuration, waterFinish);

        return (int)min(landThenWater, waterThenLand);
    }
};
