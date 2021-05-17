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

const int64_t INF = 10'000'000'000'000'000;
const int DINF = 1'000'000'000;
const int MXN = 100;
const int MXK = 1000;

//***************** GLOBAL VARIABLES *****************

int N, M, K;

int64_t buy[MXN][MXK], sell[MXN][MXK], profit[MXN][MXN], dist[MXN][MXN];

//***************** AUXILIARY STRUCTS *****************



//***************** MAIN BODY *****************

bool check(int x){
	int64_t adj[MXN][MXN];

	for(int u = 0; u < N; u++)
		for(int v = 0; v < N; v++)
			adj[u][v] = max(-INF, profit[u][v] - dist[u][v] * x);

	for(int k = 0; k < N; k++)
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				adj[i][j] = max(adj[i][j], adj[i][k] + adj[k][j]);

	for(int i = 0; i < N; i++)
		if(adj[i][i] >= 0)
			return true;

	return false;
}

void solve(){
	cin >> N >> M >> K;

	for(int i = 0; i < N; i++)
		for(int j = 0; j < K; j++){
			cin >> buy[i][j] >> sell[i][j];
			if(buy[i][j] == -1) buy[i][j] = INF;
			if(sell[i][j] == -1) sell[i][j] = -INF;
		}

	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++){
			profit[i][j] = 0;
			dist[i][j] = DINF;
		}

	for(int i = 0; i < M; i++){
		int u, v;
		cin >> u >> v;
		--u, --v;
		cin >> dist[u][v];
	}

	for(int k = 0; k < N; k++)
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

	for(int i = 0; i < K; i++)
		for(int u = 0; u < N; u++)
			for(int v = 0; v < N; v++)
				profit[u][v] = max(profit[u][v], sell[v][i] - buy[u][i]);

	int l = 1, r = 1'000'000'000, ans = 0;

	while(l <= r){
		int mid = (l + r) >> 1;
		if(check(mid)){
			l = mid + 1;
			ans = mid;
		}
		else r = mid - 1;
	}

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