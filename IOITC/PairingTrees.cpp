#include <bits/stdc++.h>

using namespace std;

const int MXN = 200'000;

vector<int> g[MXN];
int sz[MXN], N;
vector<int> centroid;

void dfs(int node, int par){
	sz[node] = 1;
	int mxc = 0;
	for(int v : g[node]){
		if(v == par)
			continue;
		dfs(v, node);
		sz[node] += sz[v];
		mxc = max(mxc, sz[v]);
	}

	mxc = max(mxc, N - sz[node]);
	if(mxc <= N / 2)
		centroid.push_back(node);
}

vector<array<int, 2>> pairing;
int p[MXN];

void dfs2(int root, int node, int par, int stree){
	p[node] = stree;
	for(int v : g[node]){
		if(v == par)
			continue;
		if(node == root) dfs2(root, v, node, v);
		else dfs2(root, v, node, stree);
	}
}

int process(int root){
	dfs2(root, root, root, root);
	vector<int> bad(N);

	for(auto& [u, v] : pairing){
		if(p[u] == p[v]) bad[p[v]]++;
	}

	int B = accumulate(bad.begin(), bad.end(), 0), x = *max_element(bad.begin(), bad.end());
	if(2*x <= B) return (B+1) >> 1;
	else return x;
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	
	cin >> N;

	for(int i = 0; i < N-1; i++){
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	for(int i = 0; i < N/2; i++){
		int u, v;
		cin >> u >> v;
		--u, --v;
		pairing.push_back({u, v});
	}

	dfs(0, 0);
	int ans = N+1;
	for(int v : centroid)
		ans = min(ans, process(v));

	cout << ans << '\n';
	return 0;
}