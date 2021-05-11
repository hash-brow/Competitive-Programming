#include <bits/stdc++.h>

using namespace std;

unordered_map<int64_t, int> dp;
int N;
vector<int> g[40];
vector<pair<int, int>> adj[40];
int dep[40], isleaf[40], par[40];

int fill(int64_t mask){
	if(dp.find(mask) != dp.end()) return dp[mask];
	if(!mask) return 0;

	int ans = 0;

	for(int i = 0; i < N; i++)
		isleaf[i] = 0;

	int total = 0;

	for(int i = 0; i < N; i++)
		if(mask & (1LL << i)){
			total++;
			isleaf[i]++;
			if(i) isleaf[par[i]]--;
		}

	// int total = __builtin_popcountll(mask);

	vector<int> leaves;
	for(int i = 0; i < N; i++)
		if(isleaf[i] == 1) leaves.push_back(i);

	vector<pair<int64_t, int>> t;

	for(int v : leaves){
		int64_t nmask = mask ^ (1LL << v);
		int rem = (N + 1 - total);
		int temp = dep[v]*rem;
		rem++;
		int cur = par[v];

		while(isleaf[cur] == 0){
			temp += rem*dep[cur];
			rem++;
			nmask ^= (1LL << cur);
			if(cur) cur = par[cur];
			else break;
		}

		// ans = max(ans, temp + fill(nmask));
		t.push_back({nmask, temp});
	}

	for(auto v : t)
		ans = max(ans, v.second + fill(v.first));
	return dp[mask] = ans;
}


void dfs(int node, int d){
	dep[node] = d;
	for(auto v : adj[node]){
		dfs(v.first, d + v.second);
	}
}

void solve(){
	dp.clear();
	for(int i = 0; i < 40; i++){
		adj[i].clear();
		g[i].clear();
	}

	cin >> N;

	// par[0] = 0;
	for(int i = 1; i < N; i++){
		cin >> par[i];
		par[i]--;
		g[par[i]].push_back(i);
	}

	for(int i = 0; i < N; i++){
		vector<int> leaf;
		for(int u : g[i]){
			if(g[u].size() == 0) leaf.push_back(u);
			else adj[i].push_back({u, 1});
		}
		if(!leaf.empty()) adj[i].push_back({leaf[0], 1});
		for(int u = 1; u < leaf.size(); u++)
			adj[leaf[u-1]].push_back({leaf[u], 0});
	}

	// for(int i = 0; i < N; i++){
	// 	cout << i << ": ";
	// 	for(auto v : adj[i])
	// 		cout << "{" << v.first << ", " << v.second << "} ";
	// 	cout << '\n';
	// }
	for(int i = 0; i < N; i++)
		for(auto v : adj[i])
			par[v.first] = i;
	
	dfs(0, 0);

	cout << fill((1LL << N) - 1) << '\n';
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 

	int t;
	cin >> t;

	for(int i = 0; i < t; i++)
		solve();

	return 0;
}