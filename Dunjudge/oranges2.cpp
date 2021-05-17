#include <bits/stdc++.h>

using namespace std;

//each fake node contains the newly added edge

struct DSU{
	vector<int> direct_par, par;
	vector<int64_t> val;  
	vector<vector<int>> adj;
	vector<int> tin, tout; 
	vector<vector<int>> up;
	int c;
	int l;   
	void init(int n){
		par.resize(2*n-1); 
		for(int i = 0; i < 2*n - 1; i++)
			par[i] = i; 

		val.resize(2*n-1); 
		adj.resize(2*n-1); 
		l = log2(2*n-1); 
		up.resize(2*n-1, vector<int>(l + 1)); 
		tin.resize(2*n-1); 
		tout.resize(2*n-1); 
		c = n; 
	}	

	int get(int x){
		if(par[x] == x) return x;
		return par[x] = get(par[x]); 
	}

	bool unite(int x, int y, int64_t weight){
		x = get(x), y = get(y); 
		if(x == y) return 0; 

		par[x] = c;
		par[y] = c;
		adj[c].push_back(x); 
		adj[c].push_back(y); 
		val[c] = max(val[c-1], weight); 
		c++; 

		return 1; 
	}

	
	int timer = 0; 

	void dfs(int node, int par){
		tin[node] = timer++;

		up[node][0] = par; 

		for(int i = 1; i <= l; i++)
			up[node][i] = up[up[node][i-1]][i-1];

		for(int v : adj[node]){
			if(v == par) continue;
			dfs(v, node);  
		}

		tout[node] = timer++; 
	}

	bool is_anc(int u, int v){
		return tin[u] <= tin[v] && tout[u] >= tout[v]; 
	}

	int lca(int u, int v){
		if(is_anc(u, v)) return u;
		if(is_anc(v, u)) return v; 

		for(int i = l; i >= 0; --i)
			if(!is_anc(up[u][i], v))
				u = up[u][i]; 

		return up[u][0]; 
	}

	int64_t ret(int x, int y){
		return val[lca(x, y)]; 
	}
}; 	
struct edge{
	int u, v;
	int64_t w; 
}; 
int main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	
	int n, e, q;
	cin >> n >> e >> q; 

	vector<edge> edges(e);
	for(auto& [u, v, w] : edges)
		cin >> u >> v >> w; 

	sort(edges.begin(), edges.end(), [](edge& a, edge& b){
		if(a.w < b.w) return true; 
		return false;
	});

	DSU s; 
	s.init(n);

	for(auto& [u, v, w] : edges)
		s.unite(u, v, w); 

	s.dfs(2*n-2, 2*n-2); 

	for(int i = 0; i < q; i++){
		int start, fin; 
		cin >> start >> fin; 

		cout << s.ret(start, fin) << '\n'; 
	} 
	return 0;
}

