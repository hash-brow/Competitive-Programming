#include <bits/stdc++.h>
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
*/

using namespace std;
// using namespace __gnu_pbds;
using namespace chrono;

// mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
/*
template <class T> using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;
*/

//***************** CONSTANTS *****************

const int MXN = 100001;
const int64_t INF = 1'000'000'000'000'000'000;

//***************** GLOBAL VARIABLES *****************

vector<array<int64_t, 2>> g[MXN];
int64_t d[3][MXN], ans;

//***************** AUXILIARY STRUCTS *****************

void dijkstra(int node, int64_t dist[]){
	priority_queue< pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>> > pq;
	fill(dist, dist + MXN, INF);

	pq.emplace(0, node);
	dist[node] = 0;

	while(!pq.empty()){
		auto [dir, u] = pq.top();
		pq.pop();

		if(dir > dist[u])
			continue;

		for(const auto& [v, w] : g[u]){
			if(dist[v] > dist[u] + w){
				pq.emplace(dist[u] + w, v);
				dist[v] = dist[u] + w;
			}
		}
	}
}

void parent(int start, int end, int64_t dist[]){
	priority_queue< array<int64_t, 3>, vector<array<int64_t, 3>>, greater<array<int64_t, 3>> > pq;
	int64_t dp[2][MXN];
	bool vis[MXN];

	fill(dp[0], dp[0] + MXN, INF);
	fill(dp[1], dp[1] + MXN, INF);
	fill(dist, dist + MXN, INF);

	memset(vis, 0, sizeof vis);

	pq.push({0, start, 0});
	dist[start] = 0;

	while(!pq.empty()){
		auto [dir, u, par] = pq.top();
		pq.pop();

		if(!vis[u]){
			vis[u] = 1;
			dist[u] = dir;
			for(const auto& [v, w] : g[u]){
				pq.push({dir + w, v, u});
			}

			dp[0][u] = min(d[0][u], dp[0][par]);
			dp[1][u] = min(d[1][u], dp[1][par]);
		}
		else if(dist[u] == dir){
			if(min(d[0][u], dp[0][par]) + min(d[1][u], dp[1][par]) <= dp[0][u] + dp[1][u]){
				dp[0][u] = min(d[0][u], dp[0][par]);
				dp[1][u] = min(d[1][u], dp[1][par]);
			}
		}
	}

	ans = min(ans, dp[0][end] + dp[1][end]);
}

//***************** MAIN BODY *****************

void solve(){
	int N, M, S, T, U, V;
	cin >> N >> M >> S >> T >> U >> V;

	for(int i = 0; i < M; i++){
		int u, v;
		int64_t w;
		cin >> u >> v >> w;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}

	dijkstra(U, d[0]);
	dijkstra(V, d[1]);

	ans = d[0][V];

	parent(S, T, d[2]);
	parent(T, S, d[2]);

	cout << ans << '\n';
}

//***************** *****************

int32_t main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);

	#ifdef LOCAL
		auto begin = high_resolution_clock::now();
	#endif

	int tc = 1;
	// cin >> tc; 
	for (int t = 0; t < tc; t++)
		solve();

	#ifdef LOCAL 
		auto end = high_resolution_clock::now();
		cout << fixed << setprecision(4);
		cout << "Execution Time: " << duration_cast<duration<double>>(end - begin).count() << "seconds" << endl;
	#endif

	return 0;
}

/*
If code gives a WA, check for the following : 
1. I/O format

2. Are you clearing all global variables in between tests if multitests are a thing

3. Can you definitively prove the logic
*/