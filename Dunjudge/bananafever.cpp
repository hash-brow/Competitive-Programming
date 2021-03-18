#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj; 
vector<int> dp[2]; //dp[1][i] -> max on taking i, dp[0][i] -> max on not taking i
vector<int> h;
vector<int> state;
void dfs(int node, int par){
	for(int v : adj[node]){
		if(v == par)
			continue; 
		dfs(v, node); 
		dp[0][node] += max(dp[1][v], dp[0][v]); 
		dp[1][node] += dp[0][v]; 
	}
	dp[1][node] += h[node]; 
}

void dfs1(int node, int par, vector<int>& taken){
	if(state[node] == 1)
		taken.push_back(node); 
	int c = state[node]; 
	for(int v : adj[node]){
		if(v == par)
			continue; 
		if(c){
			state[v] = 0; 
			dfs1(v, node, taken); 
		}
		else{
			state[v] = (dp[1][v] > dp[0][v] ? 1 : 0); 
			dfs1(v, node, taken); 
		}
	}
}
int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 

	int n; 
	cin >> n; 

	adj.resize(n); 

	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v); 
		adj[v].push_back(u); 
	}

	h.resize(n); 
	dp[0].resize(n); 
	dp[1].resize(n); 
	state.resize(n);
	for(int i = 0; i < n; i++)
		cin >> h[i]; 

	dfs(0, 0);

	int count = 0; 
	vector<int> taken; 

	state[0] = (dp[0][0] > dp[1][0] ? 0 : 1); 

	dfs1(0, 0, taken); 
	cout << max(dp[0][0], dp[1][0]) << '\n'; 
	cout << taken.size() << '\n';
	for(int v : taken)
		cout << v << ' '; 

	cout << '\n';
	return 0; 
}