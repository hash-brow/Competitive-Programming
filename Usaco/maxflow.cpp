#include <bits/stdc++.h>

using namespace std;

const int MXN = 50001;
const int lg = 19;

int up[lg][MXN], tin[MXN], tout[MXN];
vector<int> adj[MXN];

int timer = 0;

int n, q;

void dfs(int node = 1, int par = 0){
	tin[node] = ++timer;

	up[0][node] = par;
	for(int i = 1; i < lg; i++)
		up[i][node] = up[i-1][up[i-1][node]];

	for(int v : adj[node]){
		if(v == par)
			continue;
		dfs(v, node);
	}

	tout[node] = timer;
}

inline bool isAncestor(int u, int v) { return tin[u] <= tin[v] && tout[u] >= tout[v]; }

int lca(int u, int v){
	if(isAncestor(u, v))
		return u;
	if(isAncestor(v, u))
		return v;

	for(int i = lg-1; i >= 0; --i)
		if(up[i][u] && !isAncestor(up[i][u], v))
			u = up[i][u];

	return up[0][u];
}

int pref[MXN];

void dfs2(int node = 1, int par = 0){
	for(int v : adj[node]){
		if(v == par) continue;
		dfs2(v, node);
		pref[node] += pref[v];
	}
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	freopen("maxflow.in", "r", stdin);
	freopen("maxflow.out", "w", stdout);

	cin >> n >> q;

	for(int i = 0; i < n-1; i++){
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs();

	while(q--){
		int u, v;
		cin >> u >> v;
		int l = lca(u, v);
		pref[u]++, pref[v]++, pref[l]--, pref[up[0][l]]--;
	}

	dfs2();

	cout << *max_element(pref + 1, pref + n + 1) << '\n';

	return 0; 
}