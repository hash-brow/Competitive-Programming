#include <bits/stdc++.h>

using namespace std;
#include <bits/stdc++.h>

using namespace std;

const int MXN = 100001;
const int lg = 19;

int up[lg][MXN], tin[MXN], tout[MXN], chosen[MXN];
array<int, 2> edges[MXN];
vector<int> adj[MXN];

int timer = 0;
int tree[MXN];

int n, m, k;

void upd(int pos, int val){
	for(; pos <= n; pos += (pos&(-pos)))
		tree[pos] += val;
}

int query(int idx){
	int sum = 0;
	for(; idx > 0; idx -= (idx&(-idx)))
		sum += tree[idx];
	return sum;
}

int query(int l, int r){
	return query(r) - query(l-1);
}

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

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	cin >> n >> m >> k;

	for(int i = 1; i < n; i++){
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
		edges[i] = {u, v};
	}	

	dfs();

	while(m--){
		int s;
		cin >> s;
		for(int i = 0; i < s; i++)
			cin >> chosen[i];
		sort(chosen, chosen + s, [&](int a, int b){
			return tin[a] < tin[b];
		});

		chosen[s] = chosen[0];

		for(int i = 0; i < s; i++){
			int l = lca(chosen[i], chosen[i+1]);
			upd(tin[chosen[i]], 1);
			upd(tin[chosen[i+1]], 1);
			upd(tin[l], -2);
		}
	}

	vector<int> ans;
	for(int i = 1; i < n; i++){
		int u = edges[i][0], v = edges[i][1];
		if(tin[u] > tin[v])
			swap(u, v);
	
		if(query(tin[v], tout[v]) >= 2*k)
			ans.push_back(i);
	}

	cout << ans.size() << '\n';
	for(int i : ans)
		cout << i << ' ';

	return 0; 
}