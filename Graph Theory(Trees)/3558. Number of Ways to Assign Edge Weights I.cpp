//Problem: 3558. Number of Ways to Assign Edge Weights I
//Topic: Trees + BFS + Combinatorics
//Pattern: Medium

class Solution {
public:
    static const int MOD = 1e9 + 7;

    long long modpow(long long a, long long b) {
        long long res = 1;
        while (b) {
            if (b & 1) res = (res * a) % MOD;
            a = (a * a) % MOD;
            b >>= 1;
        }
        return res;
    }

    int assignEdgeWeights(vector<vector<int>>& edges) {
        int n = edges.size() + 1;

        vector<vector<int>> adj(n + 1);
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> dist(n + 1, -1);
        queue<int> q;

        q.push(1);
        dist[1] = 0;

        int maxDepth = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    maxDepth = max(maxDepth, dist[v]);
                    q.push(v);
                }
            }
        }

        if (maxDepth == 0) return 1;

        return (int)modpow(2, maxDepth - 1);
    }
};
