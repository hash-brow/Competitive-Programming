#include <bits/stdc++.h>

using namespace std;

const int MXN = 1'000'000;

vector<int> g[MXN];
int sz[MXN], st[MXN];

void dfs(int u){
	sz[u] = 1;
	for(int v : g[u]){
		dfs(v);
		sz[u] += sz[v];
		st[u] += st[v];
	}
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int N;
	cin >> N;
	int root;

	for(int i = 0; i < N; i++){
		int p, s;
		cin >> p >> s;
		if(p != -1) g[p].push_back(i);
		else root = i;

		st[i] = s;
	}

	dfs(root);

	int ans = 0;
	for(int i = 0; i < N; i++){
		ans += abs(st[i] - sz[i]);
	}

	cout << ans << '\n';

	return 0; 
}