#include <bits/stdc++.h>

using namespace std;

const int MXN = 50001;

vector<array<int, 4>> adj[MXN];
set<pair<int, int>> pq[MXN];
int tin[MXN], tout[MXN], ans[MXN];
int timer;

void calc(int node, int par){
	tin[node] = timer++;
	for(auto& [v, l, type, id] : adj[node]){
		if(type == 1 && v != par)
			calc(v, node);
	}
	tout[node] = timer++;
}

inline bool isAncestor(int u, int v){
	return tin[u] <= tin[v] && tout[u] >= tout[v];
}

void merge(int u, int v){
	if(pq[u].size() < pq[v].size()){
		swap(pq[u], pq[v]);
		// swap(u, v);
	}
	
	for(pair<int, int> x : pq[v])
		pq[u].insert(x);
}

void dfs(int node, int par, int idx){
	for(auto& [v, l, type, id] : adj[node]){
		if(type == 0){
			if(!isAncestor(node, v)) pq[node].emplace(l, v);
			continue;
		}

		if(v == par)
			continue;
		dfs(v, node, id);
		merge(node, v);
	}

	if(idx == -1)
		return;

	while(!pq[node].empty() && isAncestor(node, pq[node].begin()->second))
		pq[node].erase(pq[node].begin());
	
	if(pq[node].empty()) ans[idx] = -1;
	else ans[idx] = pq[node].begin()->first;
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	freopen("disrupt.in", "r", stdin);
	freopen("disrupt.out", "w", stdout);

	int n, m;
	cin >> n >> m;

	for(int i = 0; i < n-1; i++){
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].push_back({v, 1, 1, i});
		adj[v].push_back({u, 1, 1, i});
	}

	for(int i = 0; i < m; i++){
		int u, v, d;
		cin >> u >> v >> d;
		--u, --v;
		adj[u].push_back({v, d, 0, i});
		adj[v].push_back({u, d, 0, i});
	}

	timer = 0;

	calc(0, 0);
	dfs(0, 0, -1);

	for(int i = 0; i < n - 1; i++)
		cout << ans[i] << '\n';
	return 0; 
}