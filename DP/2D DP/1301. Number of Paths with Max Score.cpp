//Problem: 1301. Number of Paths with Max Score
//Topic: Dynamic Programming (2D DP / Grid DP)
//Pattern: Hard

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        const int MOD = 1e9 + 7;
        int n = board.size();

        vector<vector<int>> score(n, vector<int>(n, -1));
        vector<vector<int>> ways(n, vector<int>(n, 0));

        score[0][0] = 0;
        ways[0][0] = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                if (board[i][j] == 'X') continue;
                if (i == 0 && j == 0) continue;

                int best = -1;
                long long cnt = 0;

                // From top
                if (i > 0 && score[i - 1][j] != -1) {
                    if (score[i - 1][j] > best) {
                        best = score[i - 1][j];
                        cnt = ways[i - 1][j];
                    } else if (score[i - 1][j] == best) {
                        cnt = (cnt + ways[i - 1][j]) % MOD;
                    }
                }

                // From left
                if (j > 0 && score[i][j - 1] != -1) {
                    if (score[i][j - 1] > best) {
                        best = score[i][j - 1];
                        cnt = ways[i][j - 1];
                    } else if (score[i][j - 1] == best) {
                        cnt = (cnt + ways[i][j - 1]) % MOD;
                    }
                }

                // From diagonal
                if (i > 0 && j > 0 && score[i - 1][j - 1] != -1) {
                    if (score[i - 1][j - 1] > best) {
                        best = score[i - 1][j - 1];
                        cnt = ways[i - 1][j - 1];
                    } else if (score[i - 1][j - 1] == best) {
                        cnt = (cnt + ways[i - 1][j - 1]) % MOD;
                    }
                }

                if (best == -1) continue;

                score[i][j] = best;
                ways[i][j] = cnt % MOD;

                if (board[i][j] != 'S') {
                    score[i][j] += board[i][j] - '0';
                }
            }
        }

        if (ways[n - 1][n - 1] == 0)
            return {0, 0};

        return {score[n - 1][n - 1], ways[n - 1][n - 1]};
    }
};
