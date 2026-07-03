//Problem: 3620. Network Recovery Pathways
//Topic: Graph
//Pattern: Hard

class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();

        vector<vector<pair<int,int>>> g(n);
        vector<int> indeg(n,0);

        int mx = 0;

        for(auto &e: edges){
            int u=e[0], v=e[1], w=e[2];
            g[u].push_back({v,w});
            indeg[v]++;
            mx=max(mx,w);
        }

        // Topological order
        queue<int> q;
        for(int i=0;i<n;i++)
            if(indeg[i]==0)
                q.push(i);

        vector<int> topo;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            topo.push_back(u);

            for(auto &[v,w]:g[u]){
                if(--indeg[v]==0)
                    q.push(v);
            }
        }

        auto check = [&](int lim)->bool{
            const long long INF = (1LL<<60);

            vector<long long> dist(n,INF);
            dist[0]=0;

            for(int u:topo){

                if(dist[u]==INF) continue;

                // intermediate offline nodes cannot appear
                if(u!=0 && u!=n-1 && !online[u]) continue;

                for(auto &[v,w]:g[u]){

                    if(w<lim) continue;

                    if(v!=n-1 && !online[v]) continue;

                    if(dist[v] > dist[u]+w)
                        dist[v]=dist[u]+w;
                }
            }

            return dist[n-1]<=k;
        };

        if(!check(0)) return -1;

        int lo=0, hi=mx, ans=0;

        while(lo<=hi){
            int mid=lo+(hi-lo)/2;

            if(check(mid)){
                ans=mid;
                lo=mid+1;
            }else{
                hi=mid-1;
            }
        }

        return ans;
    }
};
