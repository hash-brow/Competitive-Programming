#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000000;
const int MXN = 20;

vector<int> g[MXN];

inline int cost(int mask, int node){
	int sum = 0;
	for(int v : g[node])
		sum += ((mask & (1 << v)) > 0);
	return sum;
}

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
	}

	vector<int> dp(1 << n, INF);
	for(int i = 0; i < n; i++)
		dp[1 << i] = 0;

	for(int mask = 0; mask < (1 << n); mask++){
		for(int i = 0; i < n; i++){
			if(mask & (1 << i))
				continue;
			dp[mask | (1 << i)] = min(dp[mask | (1 << i)], dp[mask] + cost(mask, i));
		}
	}

	cout << dp.back() << '\n';
	return 0; 
}