#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g, gr;
vector<int> ord;
vector<bool> vis;
vector<vector<array<int, 2>>> farthest;

vector<int> last;
int l = 0;

const int B = 320;

vector<array<int, 2>> merge(vector<array<int, 2>>& a, vector<array<int, 2>> b){
	++l;
	int n = a.size(), m = b.size(), r = 0;
	int ia = 0, ib = 0;
	for(auto& [d, v] : b)
		++d;

	vector<array<int, 2>> res;

	while((ia < n || ib < m) && r < B){
		bool t;
		if(ia == n) t = false;
		else if(ib == m) t = true;
		else if(a[ia][0] > b[ib][0]) t = true;
		else t = false;

		if(t){
			if(last[a[ia][1]] != l){
				res.push_back(a[ia]);
				++r;
			}
			last[a[ia][1]] = l;
			++ia;
		}
		else{
			if(last[b[ib][1]] != l){
				res.push_back(b[ib]);
				++r;
			}
			last[b[ib][1]] = l;
			++ib;
		}
	}

	return res;
}

void dfs(int node){
	vis[node] = 1;
	farthest[node].push_back({0, node});
	for(int v : gr[node]){
		if(!vis[v])
			dfs(v);
		farthest[node] = merge(farthest[node], farthest[v]);
	}
	ord.push_back(node);
}

void reset(int n){
	g.resize(n);
	gr.resize(n);
	vis.resize(n, 0);
	farthest.resize(n);
	last.resize(n, -1);
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, m, q;
	cin >> n >> m >> q;

	reset(n);

	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		gr[v].push_back(u);
	}

	for(int i = 0; i < n; i++)
		if(!vis[i])
			dfs(i);

	reverse(ord.begin(), ord.end());

	vector<int> d(n);

	while(q--){
		int node, y;
		cin >> node >> y;
		--node;
		++l;
		for(int i = 0; i < y; i++){
			int x;
			cin >> x;
			--x;
			last[x] = l;
		}

		if(y < B){
			int ans = -1;
			for(auto& [di, v] : farthest[node]){
				if(last[v] != l){
					ans = di;
					break;
				}
			}
			cout << ans << '\n';
		}
		else{
			int ans = -1;
			d.assign(n, -1e9);

			d[node] = 0;

			for(int v : ord){
				for(int k : g[v])
					d[v] = max(d[v], d[k] + 1);
				if(last[v] != l)
					ans = max(ans, d[v]);
			}

			cout << ans << '\n';
		}
	}
	return 0; 
}