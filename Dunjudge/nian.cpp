#include <bits/stdc++.h>
using namespace std;

struct segtree{
	vector<int64_t> st;
	int sz; 
	void init(int n){
		sz = 1; 
		while(sz < n) 
			sz *= 2; 
		st.assign(2*sz, 0); 
	}
	void build(vector<int64_t>& a, int x, int l, int r){
		if(r - l == 1){
			if(l < a.size())
				st[x] = a[l]; 
			return; 
		}
		int mid = (l + r)/2; 
		build(a, 2*x+1, l, mid); 
		build(a, 2*x+2, mid, r); 
		st[x] = st[2*x+1] + st[2*x+2]; 
	}
	void set(int idx, int64_t v, int x, int lx, int rx){
		if(rx - lx == 1){
			st[x] += v; 
			return; 
		}		
		int mid = (lx + rx)/2; 
		if(idx < mid) 
			set(idx, v, 2*x+1, lx, mid); 
		else 
			set(idx, v, 2*x+2, mid, rx); 
		st[x] = st[2*x+1] + st[2*x+2]; 
	}
	int64_t query(int l, int r, int x, int lx, int rx){
		if(rx <= l || lx >= r) 
			return 0; 
		if(lx >= l && rx <= r) 
			return st[x]; 
		int mid = (lx + rx)/2; 
		return query(l, r, 2*x+1, lx, mid) + query(l, r, 2*x+2, mid, rx); 
	}
	void set(int idx, int64_t v){
		set(idx, v, 0, 0, sz); 
	}
	int64_t query(int l, int r){
		return query(l, r, 0, 0, sz); 
	}
	void build(vector<int64_t>& a){
		build(a, 0, 0, sz); 
	}
};
struct DSU{
	vector<int> par;
	int c, l; 
	vector<vector<int>> adj, up; 
	vector<int64_t> weight; 
	vector<int> tin, tout; 
 	void init(int n){
		l = log2(2*n-1); 
		c = n; 
		adj.resize(2*n-1); 
		up.resize(2*n-1, vector<int>(l+1)); 
		weight.resize(2*n-1); 
		par.resize(2*n-1); 
		iota(par.begin(), par.end(), 0); 
		tin.resize(2*n-1); 
		tout.resize(2*n-1);  
	}

	int get(int x){
		return (par[x] == x ? x : par[x] = get(par[x])); 
	}

	bool unite(int x, int y, int64_t w){
		x = get(x), y = get(y); 
		if(x == y) return 0;  
		par[x] = c; 
		par[y] = c; 
		adj[c].push_back(x);
		adj[c].push_back(y); 
		weight[c] = max({w, weight[x], weight[y]}); 
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
	segtree val; 
	void seg_init(int n, vector<int64_t>& a){
		val.init(2*(2*n - 1)); 
		vector<int64_t> b(2*(2*n - 1), 0); 
		for(int i = 0; i < n; i++)
			b[tin[i]] = a[i]; 

		val.build(b); 
	}
	int64_t query(int x, int64_t k, int64_t p){
		val.set(tin[x], p); 

		if(val.query(tin[x], tout[x]) >= k) return 0; 
		if(val.query(tin[up[x][l]], tout[up[x][l]]) < k) return -1; 
		for(int i = l; i >= 0; --i){
			int t = up[x][i]; 
			if(val.query(tin[t], tout[t]) < k)
				x = t; 
		}

		x = up[x][0]; 
		return weight[x]; 
	}
}; 
struct edge{
	int u, v; 
	int64_t w; 
}; 
int32_t main(){
	ios_base::sync_with_stdio(NULL); 
	cin.tie(NULL); 

	int n, m;
	cin >> n >> m; 
	vector<int64_t> a(n); 
	for(auto& x : a)
		cin >> x; 

	vector<edge> edges(m); 

	for(auto&[u, v, w] : edges)
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
	s.seg_init(n, a); 
	int q;
	cin >> q; 
	
	for(int i = 0; i < q; i++){
		int start; 
		int64_t p, w; 
		cin >> start >> p >> w; 
		cout << s.query(start, w, p) << '\n'; 
	}
	return 0; 
}	