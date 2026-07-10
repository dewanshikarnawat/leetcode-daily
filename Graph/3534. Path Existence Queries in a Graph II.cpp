//Problem: 3534. Path Existence Queries in a Graph II
//Topic: Graph
//Pattern: Hard

class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int,int>> a;
        for(int i = 0; i < n; i++)
            a.push_back({nums[i], i});

        sort(a.begin(), a.end());

        vector<int> pos(n);
        vector<int> val(n);
        for(int i = 0; i < n; i++){
            val[i] = a[i].first;
            pos[a[i].second] = i;
        }

        vector<int> comp(n);
        comp[0] = 0;
        for(int i = 1; i < n; i++){
            comp[i] = comp[i-1] + (val[i] - val[i-1] > maxDiff);
        }

        vector<int> nxt(n);
        int r = 0;
        for(int i = 0; i < n; i++){
            while(r + 1 < n && val[r + 1] - val[i] <= maxDiff)
                r++;
            nxt[i] = r;
            if(r == i) r++;
        }

        const int LOG = 18; 
        vector<vector<int>> up(LOG, vector<int>(n));

        for(int i = 0; i < n; i++)
            up[0][i] = nxt[i];

        for(int k = 1; k < LOG; k++){
            for(int i = 0; i < n; i++){
                up[k][i] = up[k-1][ up[k-1][i] ];
            }
        }

        vector<int> ans;

        for(auto &q : queries){
            int u = pos[q[0]];
            int v = pos[q[1]];

            if(u == v){
                ans.push_back(0);
                continue;
            }

            if(u > v) swap(u, v);

            if(comp[u] != comp[v]){
                ans.push_back(-1);
                continue;
            }

            int cur = u;
            int steps = 0;

            for(int k = LOG - 1; k >= 0; k--){
                if(up[k][cur] < v){
                    cur = up[k][cur];
                    steps += (1 << k);
                }
            }

            ans.push_back(steps + 1);
        }

        return ans;
    }
};
