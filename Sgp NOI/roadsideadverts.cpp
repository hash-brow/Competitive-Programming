#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int64_t>>> adj;
struct LCA{
    vector<vector<int>> up; 
    int l;
    vector<int> tin, tout; 
    vector<int64_t> depth;
    LCA(int n){
        l = 32 - __builtin_clz(n);
        up.resize(l+1, vector<int>(n));
        tin.resize(n); 
        tout.resize(n);
        depth.resize(n);
        dfs(0, 0, 0);
    }
    int timer = 0; 
    void dfs(int node, int par, int64_t W){
        tin[node] = timer++; 
        depth[node] = depth[par] + W;
        up[0][node] = par;
        for(int i = 1; i <= l; i++)
            up[i][node] = up[i-1][up[i-1][node]];

        for(auto&[v, w] : adj[node]){
            if(v == par)
                continue;
            dfs(v, node, w);
        }

        tout[node] = timer++;
    }

    bool isAncestor(int u, int v){
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    int lca(int u, int v){
        if(isAncestor(u, v))
            return u;
        if(isAncestor(v, u))
            return v;

        for(int i = l; i >= 0; --i)
            if(!isAncestor(up[i][u], v))
                u = up[i][u];

        return up[0][u];
    }

    int64_t dist(int u, int v){
        return depth[u] + depth[v] - 2*depth[lca(u, v)];
    }
}; 
int32_t main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); 
        
    int n;
    cin >> n; 

    adj.resize(n); 

    for(int i = 0; i < n-1; i++){
        int u, v; 
        int64_t w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w); 
    }

    LCA d(n);
    int Q;
    cin >> Q; 
    for(int _ = 0; _ < Q; _++){
        vector<int> q(5);
        
        for(int i = 0; i < 5; i++)
            cin >> q[i];
        
        sort(q.begin(), q.end(), [&](int a, int b){
            if(d.tin[a] < d.tin[b])
                return true;
            return false;
        });
        int64_t ans = 0;

        for(int i = 0; i < 5; i++){
            int64_t w = d.dist(d.lca(q[(i+4)%5], q[i]), q[i]);
            ans += w;
        }

        cout << ans << '\n';
    }
    return 0; 
}