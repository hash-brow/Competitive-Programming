#include <bits/stdc++.h>

using namespace std;

const int MXN = 100001;
const int lg = 20;

int n, m, q;
bool active[MXN];

vector<int> adj[MXN];
int a[MXN], c[MXN];

int up[lg][MXN];
int tin[MXN], tout[MXN];
int timer = 1;

void dfs(int node = 1, int par = 0){
	tin[node] = timer++;
	a[node] = 1;

	up[0][node] = par;
	for(int i = 1; i < lg && up[i-1][node]; i++)
		up[i][node] = up[i-1][up[i-1][node]];

	for(int v : adj[node]){
		if(v == par)
			continue;
		dfs(v, node);
	}

	tout[node] = timer;
}

int tree[MXN];

void upd(int idx, int val){
	for(; idx <= n; idx += (idx&(-idx)))
		tree[idx] += val;
}

int query(int idx){
	int sum = 0;
	for(; idx; idx -= (idx&(-idx)))
		sum += tree[idx];
	return sum;
}

int findAncestor(int node){
	int lca = node;
	int ct = query(tin[node]);
	for(int i = lg-1; i >= 0; --i)
		if(up[i][lca] && query(tin[up[i][lca]]) == ct)
			lca = up[i][lca];

	return lca;
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	cin >> n >> m >> q;

	vector<array<int, 2>> edges(n-1);
	for(auto& [u, v] : edges){
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs();

	for(int i = 1; i <= n; i++){
		upd(tin[i], 1);
		upd(tout[i], -1);
	}

	for(int i = 0; i < m; i++){
		int idx;
		cin >> idx;
		--idx;
		int u = edges[idx][0], v = edges[idx][1];

		if(up[0][u] == v)
			swap(u, v);

		if(active[idx]){
			a[v] = c[v] = a[findAncestor(u)];
			upd(tin[v], 1);
			upd(tout[v], -1);
		}
		else{
			a[findAncestor(u)] += (a[v] - c[v]);
			upd(tin[v], -1);
			upd(tout[v], 1);
		}

		active[idx] = !active[idx];
	}

	for(int i = 0; i < q; i++){
		int node;
		cin >> node;
		cout << a[findAncestor(node)] << '\n';
	}
	return 0; 
}