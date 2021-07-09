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

const int MXN = 200;
const int MXM = 50000;
const int64_t INF = 1'500'000'000'000'000;

//***************** GLOBAL VARIABLES *****************

vector<array<int, 2>> g[2][MXN];
int U[MXM], V[MXM], w[MXM], rev[MXM];
int N, M;

//***************** AUXILIARY STRUCTS *****************

void dijkstra(int S, int T, int idx, int64_t dist[], vector<bool>& used){
	int prev[N]; memset(prev, -1, sizeof prev);
	
	if(!idx)
		used.resize(M, false);
	
	vector<bool> vis(N, false);

	for(int i = 0; i <= N; i++) dist[i] = INF;
	dist[S] = 0;

	while(true){
		int u = N;
		for(int i = 0; i < N; i++)
			if(!vis[i] && dist[i] < dist[u])
				u = i;

		if(u == N)
			break;

		for(auto& [v, i] : g[idx][u])
			if(dist[v] > dist[u] + w[i])
				dist[v] = dist[u] + w[i], prev[v] = i;

		vis[u] = 1;
	}
	
	if(idx) return;

	for(int cur = T; prev[cur] != -1; cur = U[prev[cur]])
		used[prev[cur]] = 1;
}

int64_t dijkstra(int S, int T, int idx){
	vector<bool> vis(N, 0);
	int64_t dist[N + 1];
	for(int i = 0; i <= N; i++)
		dist[i] = INF;

	dist[S] = 0;

	while(true){
		int u = N;
		for(int i = 0; i < N; i++)
			if(!vis[i] && dist[i] < dist[u])
				u = i;

		if(u == N)
			break;

		for(auto& [v, i] : g[0][u])
			if(i != idx){
				dist[v] = min(dist[v], dist[u] + w[i]);
			}

		if(V[idx] == u)
			dist[U[idx]] = min(dist[U[idx]], dist[u] + w[idx]);

		vis[u] = 1;
	}

	return dist[T];
}

//***************** MAIN BODY *****************

void solve(){
	cin >> N >> M;

	for(int i = 0; i < M; i++){
		cin >> U[i] >> V[i] >> w[i] >> rev[i];
		--U[i], --V[i];
		g[0][U[i]].push_back({V[i], i});
		g[1][V[i]].push_back({U[i], i});
	}

	vector<bool> used[2], tmp;
	int64_t from[2][N + 1], to[2][N + 1];

	dijkstra(0, N - 1, 0, from[0], used[0]);
	dijkstra(N - 1, 0, 0, from[1], used[1]);
	dijkstra(0, N - 1, 1, to[0], tmp);
	dijkstra(N - 1, 0, 1, to[1], tmp);

	int64_t ans = from[0][N - 1] + from[1][0];

	for(int i = 0; i < M; i++){
		int64_t temp = rev[i];

		if(used[0][i]) 
			temp += dijkstra(0, N - 1, i);
		else temp += min(from[0][N - 1], from[0][V[i]] + to[1][U[i]] + w[i]);

		if(used[1][i])
			temp += dijkstra(N - 1, 0, i);
		else temp += min(from[1][0], from[1][V[i]] + to[0][U[i]] + w[i]);

		ans = min(ans, temp);
	}

	cout << (ans >= INF ? -1 : ans) << '\n';
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