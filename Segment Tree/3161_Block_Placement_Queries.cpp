//Problem: Block Placement Queries
//Topic: Segment Tree
//Difficulty: Hard

class Solution {
public:
    struct SegTree {
        int n;
        vector<int> st;

        SegTree(int n) : n(n) {
            st.assign(4 * n, 0);
        }

        void update(int p, int val, int node, int l, int r) {
            if (l == r) {
                st[node] = val;
                return;
            }

            int mid = (l + r) >> 1;

            if (p <= mid)
                update(p, val, node * 2, l, mid);
            else
                update(p, val, node * 2 + 1, mid + 1, r);

            st[node] = max(st[node * 2], st[node * 2 + 1]);
        }

        void update(int p, int val) {
            update(p, val, 1, 0, n - 1);
        }

        int query(int L, int R, int node, int l, int r) {
            if (R < l || r < L) return 0;
            if (L <= l && r <= R) return st[node];

            int mid = (l + r) >> 1;

            return max(
                query(L, R, node * 2, l, mid),
                query(L, R, node * 2 + 1, mid + 1, r)
            );
        }

        int query(int L, int R) {
            if (L > R) return 0;
            return query(L, R, 1, 0, n - 1);
        }
    };
    vector<bool> getResults(vector<vector<int>>& queries) {
        int mx = 0;

        set<int> obstacles;
        obstacles.insert(0);

        for (auto &q : queries) {
            mx = max(mx, q[1]);
            if (q[0] == 1)
                obstacles.insert(q[1]);
        }

        SegTree seg(mx + 1);

        int last = 0;
        bool first = true;

        for (int p : obstacles) {
            if (first) {
                first = false;
                last = p;
                continue;
            }

            seg.update(p, p - last);
            last = p;
        }

        vector<bool> ans;

        for (int i = (int)queries.size() - 1; i >= 0; --i) {
            auto &q = queries[i];

            if (q[0] == 2) {
                int x = q[1];
                int sz = q[2];

                int pre = *std::prev(obstacles.upper_bound(x));

                int bestGap = seg.query(0, x);
                int tailGap = x - pre;

                ans.push_back(max(bestGap, tailGap) >= sz);
            } else {
                int p = q[1];

                auto it = obstacles.find(p);
                auto prv = std::prev(it);
                auto nxt = std::next(it);

                if (nxt != obstacles.end()) {
                    seg.update(*nxt, *nxt - *prv);
                }

                seg.update(p, 0);
                obstacles.erase(it);
            }
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};
