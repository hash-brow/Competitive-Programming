#include <bits/stdc++.h>

using namespace std;

const int MXN = 1001;
const int MXC = 30001;
const int INF = 1e9;

vector<array<int, 2>> g[MXN];
int dp[MXN][MXC];
int D;
vector<int> use[MXN];

void dfs(int node, int par){
	for(auto e : g[node]) if(e[0] != par && e[1] <= D){
		int v = e[0], d = e[1];
		dfs(v, node);
		vector<int> tmp(MXC, INF);
	
		for(int i : use[node]){
			for(int j : use[v])
				if(i + j < MXC)
					tmp[i+j] = min(tmp[i+j], dp[node][i] + d + dp[v][j]);
				else break;
		}

		for(int i = 0; i < MXC; i++){
			if(dp[node][i] >= INF/2 && tmp[i] < INF/2) use[node].push_back(i);
			dp[node][i] = min(tmp[i], dp[node][i]);
		}
	}
}

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int N;
	cin >> N >> D;
	for(int i = 0; i < MXN; i++)
		for(int j = 0; j < MXC; j++)
			dp[i][j] = INF;
	
	for(int i = 1; i <= N; i++){
		int x;
		cin >> x;
		use[i].push_back(x);
		dp[i][x] = 0;
	}

	for(int i = 0; i < N-1; i++){
		int u, v, d;
		cin >> u >> v >> d;
		g[u].push_back({v, d});
		g[v].push_back({u, d});
	}

	D >>= 1;
	dfs(1, 1);

	int ans = 0;

	for(int i = 0; i < MXC; i++)
		if(dp[1][i] <= D)
			ans = i;

	cout << ans << '\n';
	return 0; 
}