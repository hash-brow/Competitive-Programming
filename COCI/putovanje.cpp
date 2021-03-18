#include <bits/stdc++.h>

using namespace std;

const int MXN = 200001;
const int lg = 20;

vector<array<int, 3>> adj[MXN];

struct LCA{
	int up[lg][MXN];
	int tin[MXN], tout[MXN];
	int timer = 0;

	LCA(){
		dfs();
	}

	void dfs(int node = 0, int par = 0){
		tin[node] = timer++;

		up[0][node] = par;
		for(int i = 1; i < lg; i++)
			up[i][node] = up[i-1][up[i-1][node]];

		for(auto& [v, c1, c2] : adj[node]){
			if(v == par) continue;
			dfs(v, node);
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

		for(int i = lg - 1; i >= 0; --i)
			if(!isAncestor(up[i][u], v))
				u = up[i][u];

		return up[0][u];
	}
};

int pref[MXN];
int64_t ans = 0;
void dfs(int node = 0, int par = -1){
	for(auto& [v, c1, c2] : adj[node]){
		if(v == par)
			continue;
		dfs(v, node);
		pref[node] += pref[v];
		ans += min(1LL*c1*pref[v], 1LL*c2);
	}
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n;
	cin >> n;

	for(int i = 0; i < n-1; i++){
		int u, v, c1, c2;
		cin >> u >> v >> c1 >> c2;

		--u, --v;

		adj[u].push_back({v, c1, c2});
		adj[v].push_back({u, c1, c2});
	}

	LCA Q;

	for(int i = 1; i < n; i++){
		int l = Q.lca(i, i-1);
		if(l == i || l == i-1){
			pref[l]--;
			pref[l^(i-1)^i]++;
		}
		else{
			pref[l] -= 2;
			pref[i-1]++;
			pref[i]++;
		}
	}

	dfs();

	cout << ans << '\n';
	return 0; 
}