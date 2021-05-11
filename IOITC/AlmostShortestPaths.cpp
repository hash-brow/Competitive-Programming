#include <bits/stdc++.h>

using namespace std;

const int mod = 1'000'000'007;
const int INF = 1'000'000'000;
const int MXN = 500'000;
vector<int> g[MXN], levs[MXN], par[MXN], same[MXN];
array<int, 2> dp[MXN];

int32_t main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	
	int n, m;
	cin >> n >> m;


	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	queue<int> q;
	vector<int> d(n, INF);

	d[0] = 0;
	q.push(0);

	while(!q.empty()){
		int u = q.front();
		q.pop();

		for(int v : g[u]){
			if(d[v] > d[u] + 1){
				d[v] = d[u] + 1;
				q.push(v);
			}
		}
	}

	for(int i = 0; i < n; i++){
		levs[d[i]].push_back(i);
		for(int v : g[i]){
			if(d[v] == d[i] - 1) par[i].push_back(v);
			else if(d[v] == d[i]) same[i].push_back(v);
		}
	}

	dp[0][0] = 1;

	for(int i = 1; i < n; i++){
		for(int u : levs[i]){
			for(int v : par[u]){
				(dp[u][0] += dp[v][0]) %= mod;
				(dp[u][1] += dp[v][1]) %= mod;
			}
		}
		for(int u : levs[i]){
			for(int v : same[u])
				(dp[u][1] += dp[v][0]) %= mod;
		}
	}

	for(int i = 0; i < n; i++)
		cout << (dp[i][0] + dp[i][1]) % mod << '\n';
	return 0; 
}