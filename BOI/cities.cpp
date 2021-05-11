#include <bits/stdc++.h>

using namespace std;

const int MXN = 100000;
const int MXK = 5;
const int64_t INF = 1e16;

vector<pair<int, int64_t>> g[MXN];
int64_t dis[MXN], dp[1 << MXK][MXN];

int N, K;

void dijkstra(int mask){
	priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>>> pq;

	for(int v = 0; v < N; v++){
		dis[v] = dp[mask][v];
		pq.emplace(dp[mask][v], v);
	}

	while(!pq.empty()){
		auto [d, u] = pq.top();
		pq.pop();

		if(d != dis[u])
			continue;

		for(auto& [v, di] : g[u]){
			if(dis[v] > dis[u] + di){
				dis[v] = dis[u] + di;
				pq.emplace(dis[v], v);
			}
		}
	}

	for(int v = 0; v < N; v++)
		dp[mask][v] = dis[v];
}

int32_t main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int M;

	cin >> N >> K >> M;

	vector<int> imp(K);
	for(auto& v : imp){
		cin >> v;
		--v;
	}

	for(int mask = 0; mask < (1 << K); mask++)
		for(int v = 0; v < N; v++)
			dp[mask][v] = INF;

	for(int i = 0; i < M; i++){
		int u, v, w;
		cin >> u >> v >> w;
		--u, --v;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}

	for(int i = 0; i < K; i++)
		dp[1 << i][imp[i]] = 0;

	for(int mask = 1; mask < (1 << K); mask++){
		for(int smask = mask; smask; smask = (smask-1)&mask)
			for(int v = 0; v < N; v++)
				dp[mask][v] = min(dp[mask][v], dp[smask][v] + dp[smask^mask][v]);

		dijkstra(mask);
	}

	int64_t ans = INF;

	for(int v = 0; v < N; v++)
		ans = min(ans, dp[(1 << K)-1][v]);

	cout << ans << '\n';

	return 0;
}