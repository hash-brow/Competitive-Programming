#include <bits/stdc++.h>

using namespace std;

struct dsu{
	vector<int> e; 
	dsu(int n){
		e.assign(n, -1);
	}
	int get(int x){
		return (e[x] < 0 ? x : e[x] = get(e[x]));
	}
	bool unite(int x, int y){
		x = get(x), y = get(y); 
		if(x == y)
			return 0; 
		if(e[x] > e[y])
			swap(x, y); 
		e[x] += e[y]; 
		e[y] = x; 
		return 1;
	}
};

vector<bool> cur, vis;
vector<vector<int>> adj, ans;
vector<int> parent;
int dfs(int node, int par){
	vis[node] = 1;
	parent[node] = par;
	vector<int> child;
	for(int v : adj[node]){
		if(v == par)
			continue;
		int c = dfs(v, node);
		if(c != -1)
			child.push_back(c);
	}
	if(cur[node]) child.push_back(node);
	for(int i = 1; i < child.size(); i += 2){
		int one = child[i], two = child[i-1];
		vector<int> f, s;
		while(one != node){
			f.push_back(one);
			one = parent[one];
		}
		while(two != node){
			s.push_back(two);
			two = parent[two];
		}
		f.push_back(node);
		reverse(s.begin(), s.end());
		for(int v : s) f.push_back(v);
		ans.push_back(f);
	}
	if(child.size() & 1) return child.back();
	return -1;
}
int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, m;
	cin >> n >> m; 
	adj.resize(n); 
	cur.resize(n); 
	parent.resize(n);
	vis.resize(n);
	for(int i = 0; i < n; i++){
		bool x;
		cin >> x;
		cur[i] = x;
	}

	dsu d(n);
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		if(d.unite(u, v)){
			adj[u].push_back(v); 
			adj[v].push_back(u);
		}
	}
	for(int i = 0; i < n; i++)
		if(!vis[i])
			dfs(i, i);
	cout << ans.size() << '\n';
	for(auto v : ans){
		cout << v.size() << ' ';
		for(auto x : v)
			cout << x << ' ';
		cout << '\n';
	}
	return 0; 
}