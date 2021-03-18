#include <bits/stdc++.h>

using namespace std;

int n, l, timer;
vector<vector<int>> adj, up;
vector<int> tin, tout;

void dfs(int node, int p){
	tin[node] = ++timer;

	up[node][0] = p;

	for(int i = 1; i <= l; i++)
		up[node][i] = up[up[node][i-1]][i-1];

	for(int v : adj[node])
		if(v != p)
			dfs(v, node);

	tout[node] = ++timer;
}
bool is_anc(int u, int v){
	return (tin[u] <= tin[v] && tout[u] >= tout[v]);
}
int lca(int u, int v){
	if(is_anc(u, v))
		return u;
	if(is_anc(v, u))
		return v;

	for(int i = l; i >= 0; --i)
		if(!is_anc(up[u][i], v))
			u = up[u][i];

	return up[u][0];
}
void preprocess(int root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root);
}
int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	int m, q; 
	cin >> n >> m >> q;

	adj.resize(n); 

	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		--u, --v; 
		adj[u].push_back(v); 
		adj[v].push_back(u); 
	}

	preprocess(0); 

	vector<multiset<int>> lcas(n); 	
	vector<int> arr(m); 

	for(int i = 0; i < m; i++){
		cin >> arr[i]; 
		--arr[i]; 
		lcas[arr[i]].insert(i); 
	}

	for(int i = 0; i < m - 1; i++){
		int r = lca(arr[i], arr[i+1]); 
		lcas[r].insert(i); 
	}

	for(int Q = 0; Q < q; Q++){
		int type;
		cin >> type; 
		if(type == 1){
			int i, v;
			cin >> i >> v; 
			--i, --v; 
			
			if(i > 0){
				int r = lca(arr[i], arr[i-1]); 
				lcas[r].erase(lcas[r].find(i-1)); 
				lcas[lca(arr[i-1], v)].insert(i-1); 
			}
			if(i < m -1){
				int r = lca(arr[i], arr[i+1]); 
				lcas[r].erase(lcas[r].find(i)); 
				lcas[lca(arr[i+1], v)].insert(i); 
			} 
			lcas[arr[i]].erase(lcas[arr[i]].find(i)); 
			arr[i] = v; 
			lcas[v].insert(i); 
		}
		else{
			int l, r, v;
			cin >> l >> r >> v; 
			--l, --r, --v; 	
			auto it = lcas[v].lower_bound(l); 
			int ax = -2, ay = -2; 
			if(it != lcas[v].end() && *it <= r){
				int idx = *it; 
				if(arr[idx] == v)
					ax = idx, ay = idx; 
				else if(idx < r)
					ax = idx, ay = ax + 1; 
			}
			cout << ax+1 << ' ' << ay+1 << '\n';
		}
	}
	return 0; 
}